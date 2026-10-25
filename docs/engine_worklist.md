# Engine worklist

Open items in the engine units that are already started. Addresses are PROTOPC_2025.

## camera/director.cpp (0x107DD9D0 - 0x107DEAA0)

- `0x107DDB80` (`ret 0xC`) and the one-byte `ret` functions at `0x107DDC30` - `0x107DDC60`: empty functions whose
  owner is unknown (probably default virtuals of camera classes).
- `Director::Update` 98.6 %, `~Director` 93.7 %, `StartTransition(Name)`: EQUIVALENT (see the source comments).

## system/enginememory.cpp (0x107DEAC0 - 0x107DF3A0)

- `0x107DECD0` (heap kind name) takes its argument in `eax`, and `OnAllocFail` (`0x107DED20`, not in
  functions.tsv, about 0x1D6 bytes) calls it that way. MSVC 2005 only gives static functions a register convention
  under link-time code generation (`/GL`), so neither can match with plain `/O2`.
- `0x107DEAC0`, `0x107DEAD0`, `0x107DEF40` (`ret`) and `0x107DEF30` (`return 0`): owners unknown.

## controller/inputsystem.cpp (0x107DF3B0 - 0x107E059A)

The unit is complete except for these EQUIVALENT functions:

- `PushContext` / `PopContext`: the context count is addressed `[index + base]` where the engine has
  `[base + index]`.
- `Update`: the tail call goes through `edx` where the engine uses `eax`.
- The constructor: in the last loop the engine keeps `i` in `ecx` and stores `contexts` after the first compare.
- `UpdatePlayers`, `StopVibration`, `SetManager`: register choice or a reload the engine makes.
- `UpdateRemote`: the engine inlines finder / remover helpers that our compiler declines to inline (inline budget);
  the hand-expanded loops differ in load order.
- Unreferenced kept copies not reproduced yet: `0x107DF450` (`bool` at 0), `0x107DF460` (`operator==` of a 4-byte
  value), `0x107DF4D0` (`InputSystem::GetControllerCount`, declared but unused).

Lesson: inline accessors whose kept copies sit in the unit were used by the unit's code. Writing the code through
them (instead of the field expressions) changes inlining and register allocation; `SetFactory` only matched once
it used `GetInput` / `SetInput`.

## system/poimanager.cpp (0x10825AF0 - 0x10826776)

Complete except two EQUIVALENT functions: the `WorldStreamerPOI(GameObjectHandle)` constructor (the engine keeps
the handle serial in memory for the table check) and `WorldStreamerPOI::GetPosition` (the engine checks the handle
twice, IsValid then Get; our build folds the second check). Lessons from this unit:

- `math::Vector` has a user-defined copy constructor (copy construction is `fld` / `fstp` per component) and a
  `(x, y, z)` constructor (a by-value `Vector(x, y, z)` argument is built in place with `movss`).
- `GameObjectHandle`'s own constructor is inline over a base whose constructor (`0x107EE330`) is out of line:
  callers take the temporary's address again after the call instead of using the returned `this`.
- The engine's asserts keep a per-site `static bool` and pass file, line, expression text and message to
  `core::ReportError` (`OLD_ASSERT_AT` in `code/core/debug.h`).

## gameobject/details/mastertable.cpp (0x107E1D20 - 0x107E2420)

Complete except `Allocate`, `Move` and `Replace` (EQUIVALENT: register choice; Move / Replace merge the count copy
into one xor / and / xor insert where the engine keeps SetCount's and / or). Not reproduced yet: the kept copies
`0x107E1E20` (Entry::GetObject), `0x107E1E80` (GameObjectHandle::GetSerial), `0x107E1EB0` (ArrayFixed constructor),
`0x107E1F30` / `0x107E21C0` (empty) and `0x107E2400` / `0x107E2410` (ArrayFixed Clear / Reset) are not emitted
because nothing in the unit uses them. `0x107E2420` is the out-of-line MasterTable constructor (matched). `0x107EE340` is HandleBase's
(index, serial) constructor. Lesson: a `bool` inline returning a bit-field compiles to `shr; test` in conditions,
an `unsigned int` one to `test mask`.

## gameobject/behaviour.cpp (0x107EE450 - 0x107EEBBA)

Complete (47 functions with the reflection templates). Lessons:

- The reflection library (`code/content/metatype.h`): each reflected class builds its meta types in function-local
  statics (`GetPrimitiveMetaType<T>`, `GetMemberMetaType<C, T>`) and a member table; the type codes are short string
  literals ("p", "pn", "n"). PrimitiveMetaType<T>'s twelve content-library slots are declared only and mapped in
  symbols.txt to the incremental link thunks the engine's vftables hold (objcmp checks vftable words against them).
- A setter given as a pointer to a virtual member produces the compiler's vcall thunk (`??_9Behaviour@...`), which
  the engine kept as a function of the unit.
- Template members defined outside the class without `inline` are called, not inlined (BitField); their bit index is
  an int shifted as `1 << (unsigned char)bit`.
- A `bool` result written as `x == y ? true : false` drops the `xor eax, eax` before `sete`.

## gameobject/gameobjectsystem.cpp (0x107EEBC0 - 0x107F09D0)

In progress. Done: handle and registration helpers, iteration, creation, deferred updates, handle operations,
InitGameObjectSystem, ReleaseReadyGameObjects, the shutdown, FindGameObject / SearchGameObject, the channel functions
(GetListeners, SendMessage, PostMessage, CountListeners), plus the kept copies of the container, iterator, LoadInventory
and MessageRouter helpers. EQUIVALENT: SendMessage / PostMessage / CountListeners (the engine keeps the handle
iterator in a register and copies the end iterator every round), GetGameObjectName (the serial is compared again for
Get after IsValid), MoveHandle (the engine resolves the handle twice),
ClearGameObjectSystem (the engine loads gDeferredObjects before storing the router's list end) and
ShutdownGameObjectSystem (its inlined ArrayDynamicHeap destructor keeps the loaded begin pointer; a local copy in the
destructor fixes it but breaks `container::Destroy<MessageListenerList>`). Also UpdateGameObjects (0x107F0410). Left: `Iterator::Next<GameObject>`
(0x107EF2E0: the engine does not jump-thread the null result of the inlined NextObject) and small kept copies.
Lessons:

- The "update group" is content::LoadInventory (RTTI); game objects are LoadObjects kept by name, and the names are
  core::Name references.
- container::ArrayFixed keeps its elements in raw storage, not `T data[N]`: with a real array the compiler destroys
  all N elements in the array's destructor, and the engine's destructors only destroy [data, end).
- A constructor that tests its bool parameter (not the member it stored) lets the compiler drop the test for a
  constant argument; the engine's locked LoadInventory::Iterator has a separate one-argument constructor.
- A dead loop (`while (bit != 0x400) bit <<= 1;` with an unused result) is left in by the compiler.
- UpdateGameObjects takes a 12-byte context by value (the callers copy three words); the time step is its last word.
  Reading the object again for an argument (`GetHandle((GameObject*)it.entry->GetObject())`) instead of reusing the
  local fixed the register allocation of the whole loop.
- A function with more than a page of locals calls `__chkstk` (the engine's `__alloca_probe`, 0x10A883B0); it is
  mapped in symbols.txt.
- `__RTDynamicCast` is an import stub (0x10A88356); leave it out of symbols.txt, the relink takes it from
  msvcr80.lib. The RTTI type descriptors `??_R0...@8` it is passed are mapped as data.

## gameobject/gameobject.cpp (0x107E05A0 - 0x107E1D20)

First part: the constructor, destructor and scalar deleting destructor, vftable slots 0 - 5 (AddRef / Release
forward to LoadObject, slot 3 registers the object, IsReady, slot 5 ends construction), the construction helpers
(heap and object in thread-local slots), SendMessage / PostMessage, SetTransform / SetPosition, the controller
forwards, FindAttribute, SetActive, AddAttribute and AddDynamicAttribute. EQUIVALENT: RemoveDynamicAttribute (the
engine saves esi / edi before testing for the list). Second and third parts: the reflection data (GetClassInfo
and GetMembers of AttributeEntry, DynamicAttributeList and GameObject), the content meta type getters (class, name,
object and ArrayDynamic meta types), MemberOffset, the MetaInstanceHelper / ArrayDynamicHelper templates and the
ArrayDynamic<AttributeEntry> members they use. Left: 0x107E1CD0 (sends AttributeUpdatedMessage), 0x107E1500
(Compact), the uninitialised copy / fill helpers and a few duplicate one-instruction copies. Lessons:

- The "behaviour container" is engine::BehaviourController (RTTI); its 64-bit listen mask is at +0x20 and the update
  mask at +0x28.
- content::LoadObject's reference count is volatile: the LoadObject vftable store survives in the GameObject
  constructor only because the volatile store after it stops dead-store elimination.
- Members set in the constructor before a member object's constructor call are in the initialiser list.
- Placement new on a "room for one more" helper (`new (array.Grow()) T(...)`) gives the engine's null-checked
  in-place construction; Size / Capacity are signed (`sar`) and a capacity read once into a local keeps the shifts.
- `x ? false : true` gives `test; sete` where `!x` gives `neg; sbb; add`.
- Vftable slots a class inherits without overriding are mapped to the incremental link thunks the vftables hold.
- content::MemberOffset is a template on the member type (MemberOffset<unsigned char> is 0x10568950,
  <core::Name> 0x10066120); each new member type gets a copy in the unit that first uses it. Templates defined in a
  header without `inline` stay calls, so the meta type getters (GetClassMetaType<T>, GetObjectMetaType<T>,
  GetNameMetaType<Key>, GetArrayDynamicMetaType<Owner, A>) are templates; a plain inline getter gets inlined.
- The real container is container::ArrayDynamic<T, Allocator> (RTTI); ArrayDynamicHeap<T> is the
  AllocatorCoreAligned<16> instance. Size / Capacity are unsigned.
- A function-local static with a destructor registers it with `_atexit` (0x10A882DA, mapped in symbols.txt).

## scenariomessage.cpp (0x107F09D0 - 0x107F1960)

Complete (76 functions): engine::ScenarioMessage's GetHandle / SetHandle / WriteEvent, the WriteFields and Clone of
the engine's scenario messages (NullMessage, ScenarioInitializeMessage, StringMessage, the trigger, object, NIS and
stream package messages), TriggerMessage's and StringMessage's constructors, the trigger messages' reflection data
and every kept copy (constructors, destructors, scalar deleting destructors, base class casters). The file name is a
guess (no assert path). Lessons:

- Slot 1 of a scenario message copies it into caller memory: placement new of the class's ordinary constructor, then
  the handles, as many as the class's handle info (20-byte statics at 0x111BD558 + 0x14 n) says.
- The meta type getters are templates on the owning class (GetNameMetaType<EnterTriggerMessage>, ...), so every
  class gets its own copy.
- A class whose base has a reflected type stores its base meta type and a content::BaseClassCasterImpl<B, D> in its
  MemberList (members +8 / +0xC).
- `if (a == 0) return false; if (!b) return false;` keeps both early-out branches where `a == 0 || !b` merges them.

## gameobject/behaviourcontroller.cpp (0x108390F0 - 0x1083AD20)

engine::BehaviourController, the GameObject's behaviour list (the GameObject member `behaviours` at +0x20): construction
and destruction, the per-message dispatch table shared through a pool of reference-counted tables, the update pass
mask and per-behaviour schedule (time slicing, frame skip, phase), message listening masks, message handling,
removal, type queries and the reflection data. UpdatePasses and UpdateBehaviours are equivalent; everything else
matches. The file name is a guess (no assert path). Lessons:

- The schedule entry's flags are bitfields (13 pass bits, updated, scheduled, active) in a union with the 16-bit
  word; a set written as `if (x) bit = 1; else bit = 0;` gives the engine's `or` / `and` pair.
- Branches the compiler tail-duplicates need the same locals assigned in both arms, or it merges them.
- `dt = updateTimeScalar * dt` (reusing the parameter) keeps the engine's single stack slot.
- Parameters the callers push without extension (`push al`) are `unsigned char`, not bool.
- UpdateBehaviours' second loop tests `(!dirty && entry.IsScheduled()) || (dirty && entry.IsActive())`: the
  ternary form materialises the bit, the two-armed form gives the engine's branches (still EQUIVALENT: registers).
- GameObject::IsRegistered is out of line: the controller calls a copy at 0x107E0780 instead of inlining it.
- The controller overrides Behaviour's slot 0 (0x1083AC70, called by GameObject::Slot5 when construction ends): it
  compacts the behaviour list through a range-constructed copy and a swap (container::CompactSwap; `copy.Swap(array)`,
  not `array.Swap(copy)`), moves the schedule and message masks into the construction heap with container::Swap,
  then gives every behaviour its slot 0. Without the override the game crashed while loading although every
  function matched: tools/vtcheck.py now compares vftables.

## gameobject/gameobjectspawner.cpp (0x107F22C0 - 0x107F27D0)

engine::GameObjectSpawner: builds game objects from a content::MetaObjectTemplate (slot 9 of the template) in a heap,
adds them to an inventory, stamps the template's name into their "meta object template" attribute and, on request,
takes them off the message channel of their "packageName" attribute. Complete except two EQUIVALENT functions:
the constructor (the transform address is computed before the reference count store) and the main Create (stack
slot sharing: the engine packs the heap statistic, the attribute lookup and the handle into one slot and puts the
attribute writer at +8; that looks like 8-byte alignment of core::Name, which the other users lay out at 4).
`0x107F27D0` (`mov eax, [ecx]`, unreferenced) is not placed yet. Lessons:

- A pointer-or-default argument written as `if (p == 0) p = global;` before the call compiles to `cmove`; the
  ternary inside the argument list gives a branch.
- Attribute access goes through out-of-line templates of other units (GetAttributeWriter<T> 0x10081FE0, whose
  writer sends AttributeUpdatedMessage from its destructor through 0x107E1CD0, and GetAttributePtr<T> 0x1006AD60)
  wrapped by an inline GetAttributeValue<T>: the struct temporary dies inside the wrapper, which is what lets the
  engine reuse its stack slot.
- The message router's "value" is a channel (const MessageListeners&, a core::Name); RouterAdd / RouterRemove /
  RouterQuery were retyped.
- A meta type getter's static caster vftable is checked as a constant: leave an inline template's slot functions
  unmapped when the original vftable holds incremental link thunks for them.

## online/onlinelua.cpp (0x107F27E0 - 0x107F2970)

The script helper online_DeterminePlayerIndex and the questions behind it (CharacterQueryPlayerControlStateMessage,
the input slots' local ids), with the unit's script registration. Three EQUIVALENT functions: IsLocalSlot (`sete`
into the masked register) and the two handle helpers, which hit the open IsValid-then-Get problem: the engine
compares the handle's serial again for Get, our build folds it (also poimanager.cpp; `IsValid() { return Get() != 0; }`
does not change that). Tested in game: `online_DeterminePlayerIndex(PLAYER_1)` answers 0. Lessons:

- Units register script functions with LuaScriptManager::SetOwner(&static), Register<R, A>(name, function) (out of
  line per instantiation, in other units) and ClearOwner; Unregister(&static) removes them. The class (first called
  ScriptContext here) is engine::LuaScriptManager in code/engine/luascriptmanager.h.
- `GetScriptManager()->Unregister(x)` pushes the argument before the call; the engine calls first, through a named
  local.

## physics/supportinglimb.cpp (0x107F2970 - 0x107F66E0), first part

SupportingLimbDefinition (reflected loader object, 21 members), SupportingLimbDefinitionList, SupportingLimb (state of
one limb) and SmoothingVelocityMap: reflection, constructors, destructors, copy / swap, SetDefinition and the
explicitly instantiated containers (container::ArrayCDynamic<T, N>, an inline array of N with an end pointer, and
the new[]-based array the RTTI calls ArrayDynamic<T, AllocatorNew>, kept here as container::ArrayDynamicNew).
Six class functions are EQUIVALENT (see the source). Open:

- Container members that do not match yet (left unmapped, the engine's copies stay): ArrayDynamicNew::Create /
  Allocate / Erase / Reserve / Insert, ArrayCDynamic Erase / ShiftUp / Insert (Entry), the UninitializedFill and
  CopyRange copies, the helpers' Insert / Erase. Mostly register allocation.
- 0x107F3020, 0x107F31A0, the empty functions 0x107F2F40 / 0x107F31E0 - 0x107F3200 / 0x107F3CC0 - 0x107F3CE0: owners
  unknown (more identical copies than names).

Second part (runtime, 12 functions: 7 match, 5 EQUIVALENT): the cast input / result structs (CastInput 0x58 bytes:
ignore word, frame, down, start offset, extra length; CastResult 0x28 bytes, constructed with 1e12 / -1 / 0xff),
CastRay (a ravenphysics segment query from the limb origin along `down`, through the engine's shared hit buffer
0x107E6CD0 / 0x107E3C30 / 0x107E3C20 and `ravenphysics::Context::CastRay` 0x106593A0 on the context 0x1128356C; the
nearest hit whose normal faces the cast within cosineSupportAngleTolerance), Cast (the random rays on a circle of
randomRayCircleRadius around the origin, keeping the nearest), ResetDirection, GetSupportPlane and the free helpers
SmoothValue, SmoothDirection, CrossAxes, AlignAxis, OrientAxes (ORIENTATION_AXIS: axis % 3 is the matrix row, axis / 3
the sign; the third axis of a pair comes from a 3x3 table). The physics library's types live in
`code/ravenphysics/context.h` (the definition's properties plus the word behind them are one 12-byte
IntersectionFilter, copied whole into the query). Validation (2026-10-12): free roam, sprint, jump, fight, teleport.

| Address | Guess | Notes |
|---|---|---|
| 0x107F2B20 | GetSupportPlane | EQUIVALENT: end point computed x, z, y in the engine (y as length * normal.y) |
| 0x107F3560 | AlignAxis | EQUIVALENT: axis in esi / direction in ecx in the engine, ecx / edx in ours |
| 0x107F36C0 | SmoothDirection | EQUIVALENT: load order of the direction and the dot product's sum order |
| 0x107F5540 | CastRay | EQUIVALENT: this in edi and an 8 byte larger frame in the engine |
| 0x107F5AC0 | Cast | EQUIVALENT: result flag in bl in the engine, the two matrices swapped on the stack |
| 0x107F5D20 | Update | EQUIVALENT: the engine calls its kept copy of SmoothingVelocityMap::IsEmpty (0x107F3210), ours inlines it |

Update (2.4 KB) casts for a move of the character from the previous to the current frame (a second, predicting cast
from the new frame when the first finds the ground beyond the resting length), turns the random rays that found
nothing, smooths the limb's length (SmoothValue with the velocity map or the linear / fractional limits) and its
direction (SmoothDirection towards the surface normal), orients the character frame (OrientAxes / AlignAxis against
the up vector) and finally moves `current` across the cast direction so that the limb's end stays on the support.

**Bug found on 2026-10-12 (since part 1):** every character fell over sideways in the hybrid. The cause was the class
key: the original's RTTI names `.?AUSupportingLimbDefinitionList@engine@@` (a struct), ours was a class, and the
game's `dynamic_cast` (LoadInventory::DynamicCaster) compares type names, so the cast to the list returned null and
no character got its limb definitions. Byte matching and the slot check cannot see this; vtcheck now compares the
class key of every vftable's RTTI type too (it found 20 more, fixed in the same commit).

**Second bug (same day): pedestrians sank to their knees.** CastRay stored the input's word into the query's flags
(+0x24, which must stay 3) instead of the filter's last word (+0x20): a `mov [esp+0x78]` right after a `push` is
`[esp+0x74]` of the frame. Alex's limbs still found the ground, the pedestrians' did not. Found with a differential
build: the original CastRay kept, ours compiled under another name, Cast calling both and logging every difference.
Count the pending pushes when reading stack stores; an EQUIVALENT function is only as good as that reading.

Matching notes: a `Set(a, b, c)` call (arguments evaluated before any store) is what makes a cross product load all six
components first; component-wise row stores through a `Vector&` to the matrix row give the engine's pointer forms;
`Clamp(t, 0, 1)` sometimes becomes a different branch layout than two explicit `Select`s; `-v` is `-0.0f - x` (subss).

Lessons:

- Runs of tiny unreferenced functions are explicit instantiations (`template class X<...>;`): every member gets a copy.
- The member meta type getters are one instance per member (PrimitiveMetaType / VectorMetaType statics), so the getter
  is a template with an id; use the member index, not __LINE__ (any edit would rename the symbols).
- ArrayCDynamic keeps raw storage: constructing the array does not construct its elements.
- math::Matrix has a user-defined (inlined) copy constructor like Vector's: copies move element by element (movss).
- A loop that leaves through `break` into a bool result (`sorted = false; break;`) matches where `return false` in the
  loop does not.
- scratchpad tool kept2.py (in-process byte comparison) replaces kept.py: seconds instead of an hour.

## motiontrackingfilter.cpp (0x107FC800 - 0x107FE2A6)

engine::MotionTrackingFilter and its reflected filters (Rigid, DampedLinear, SpringBasedLinear, DampedAngular,
SpringBasedAngular): each update moves a tracked transform with its velocities and accelerations (MotionState, 0x74
bytes, name guessed) towards a target transform. Reflection data, constructors, the inline destructors and scalar
deleting destructors, the base class casters, the member meta types, MotionState's constructor and velocity updates
and the rotation delta helper all match (51 functions). The directory and file name are guesses (no assert path).

| Function | Status | Why |
|---|---|---|
| 0x107FCEF0 SpringBasedLinearMotionFilter::Update | EQUIVALENT | scheduling: the engine reloads the state's velocity for each use |
| 0x107FD340 DampedAngularMotionTrackingFilter::Update | EQUIVALENT | else branch: axis.y / axis.z loaded into a register where ours multiplies from memory |
| 0x107FD580 SpringBasedAngularMotionFilter::Update | EQUIVALENT | as SpringBasedLinear |

Lessons:

- /fp:fast reorders commutative sums freely: `x*x + y*y + z*z` and `z*z + y*y + x*x` compile alike. The engine's
  `(z*z + y*y) + x*x` length came from math::DistanceSquared(a, b) (Sub into a local, then Dot), not from Dot.
- A position read as a by-value temporary (`Vector p(m.m[3][0], m.m[3][1], m.m[3][2])`) loads all three components
  into registers first (reg-reg subtracts); writing the field expressions folds the loads into the arithmetic.
- `Vector& acceleration = state.linearAcceleration; acceleration.Sub(...); acceleration.Scale(dt);` reproduces the
  engine's load / multiply / store per component where the same calls on `state.linearAcceleration` let the compiler
  hoist the loads. A reference local for the velocity fixed DampedAngular's first branch the same way.
- fabsf of a value then multiplied stays on x87 (`fabs; fmul`); the engine stores the fabs results first (a separate
  Vector of magnitudes), then multiplies with SSE.
- `float dt = step.dt;` as a plain copy becomes an x87 `fld / fst` spill; using `step.dt` in the expressions keeps one
  SSE load.
- Inline virtual destructors in the class body are inlined into the scalar deleting destructor and still emitted as
  7-byte COMDATs (the engine's unreferenced `mov [ecx], base vftable; ret` copies); out-of-line ones are called.
- An `angle > pi` fold-back negating the axis (`axis = -axis`) needs all three negations computed before the stores
  (a temporary Vector), not Set(-x, -y, -z) or three assignments.

## database/gamedatabase.cpp (0x107F6B30 - 0x107F9F49)

engine::GameDatabase (the RTTI name; the engine's earlier "Console" guesses for it are renamed): the named subjects
(int, float, string and wide string values per player) the scripts, the front end and the online helper read and
write, kept in a `container::Map<unsigned __int64, DBSubject*, AllocatorCoreStatic<0x80,16>>` keyed by the name hash.
The unit has the subject API, the input / online / storage / front end callbacks, profile building, the db_* script
functions (registered through engine::Function wrappers, `MethodN` / `ClosureN`, and the inline
`LuaScriptManager::RegisterMethod` templates) and Create / Destroy. 60 functions match, plus 111 kept copies (the
method wrappers, the registration templates, the inline callback base members, the Map / SList members and the
scalar deleting destructors). The file name is a guess (no assert path); DBSubject, OnlineGameDBHelper,
GameDBStorage and GameDBHelper live in other units and are only declared.

| Function | Status | Why |
|---|---|---|
| 0x107F6C50 FindPlayer | EQUIVALENT | register choice and block layout: the engine saves edi on entry and keeps the player in edi |
| 0x107F6E30 StorageSlot3 | EQUIVALENT | the engine adds the member offset to ecx before loading the vftable |
| 0x107F6E40 StorageSlot4 | EQUIVALENT | as StorageSlot3 |
| 0x107F71F0 SetIntValue | EQUIVALENT | the engine spills `scope == 1` to a stack slot before pushing the arguments |
| 0x107F72B0 SetFloatValue | EQUIVALENT | as SetIntValue |
| 0x107F7380 SetStringValue | EQUIVALENT | as SetIntValue |
| 0x107F8DB0 BuildProfile | EQUIVALENT | `add eax, -4` where ours has `sub eax, 4` |

Unreferenced kept copies not reproduced: 0x107F6FB0, 0x107F6FE0, 0x107F70A0, 0x107F7170, 0x107F7180, 0x107F7190,
0x107F75C0, 0x107F75E0, 0x107F7600 (small Map / SList / allocator members whose exact form is unknown).

Lessons:

- The script wrappers read their arguments one after another (`A1 a1 = *(const A1*)arguments++; ...`) in a static
  `Call(object, arguments, result, method)`, and `ClosureN::Invoke` calls `MethodN::Invoke(object, ...)` explicitly;
  the result is stored only `if (result != 0)`.
- `RegisterMethod` is an inline member template defined out of the class; the engine emits it as a kept copy per
  instantiation, next to the wrappers' members.
- Template members defined out of the class without `inline` (core::Name's hash constructor and GetHash) are
  emitted as calls, but the optimizer still knows they are pure: repeated GetHash calls are merged and hoisted.
- Lookups copy the map pointer into a local first (`SubjectMap* map = subjects;`) and name the found subject
  (`DBSubject* subject = it->value;`) to get the engine's load order.
- SList needs its (empty) allocator member: sizeof 0x10, which the engine's SList::Size loop and `new` sizes show.
- `ResetSubject` / `ResetInt` / `ResetFloat` reset the subject twice (engine behaviour, kept).

## system/streampackage.cpp (0x107F9F50 - 0x107FBE3C)

engine::StreamPackage (RTTI; a reflected MetaLoadObject with slotGroup, prerequisites, resources, tags, sync,
xenonMaxSize, inventoryInitialSize) and its run-time half, StreamPackageInstance (name guessed, 0xA0 bytes): the
nine-state load machine over engine::streampackagestates (states and their transition table in this unit, the
states themselves in another), the inventory, the resource loaders and the stream clients. 58 functions match, plus
63 kept copies (the lists' members, StringDynamic, the string / primitive meta type getters and setters, the member
meta type getters, the scalar deleting destructors). The directory and file name are guesses (no assert path). The
reflected setters of tags / sync / inventoryInitialSize were folded by the linker with identical functions of other
units (0x104E13C0 / 0x104E13D0 / 0x104E13E0), so they are compiled but not annotated.

| Function | Status | Why |
|---|---|---|
| 0x107F9FA0 StreamPackageInstance::Update | EQUIVALENT | the engine adds the state to request * 9 as a memory operand and reloads it for the comparison |
| 0x107FA050 StreamPackageInstance::CreateInventory | EQUIVALENT | register choice in the AddRef call |
| 0x107FBC90 StreamPackage(const Name&) | EQUIVALENT | scheduling of the reference count store |
| 0x107FBDC0 StreamPackage() | EQUIVALENT | as the other constructor |

Unreferenced kept copies not reproduced: 0x107FA240 / 0x107FA260 / 0x107FA280 (`mov eax, ecx`), 0x107FA2A0 /
0x107FAF40 (a cdecl `if (p) *p = value`), 0x107FAE40 / 0x107FAE70 (`mov eax, [ecx]`) and the one-byte `ret`s.

Lessons:

- StringDynamic's constructor is inlined into `new String(name)` but not into `new String(text, StreamAllocator())`:
  one in-class constructor with a defaulted allocator argument gives both call sites; a separate out-of-class
  template constructor for the explicit form was not needed.
- A countdown that reads `[base + i*4 - 4]` and then `[base + i*4]` after the decrement is `while (i-- != 0)` with
  both accesses at `[i]`, not `[i - 1]` / `--i`.
- Find-and-erase loops that keep the end pointer in a register across the erase need a local end that is reloaded
  after the erase (`end = list.end;`), placed before any following push.
- A state machine loop that keeps a constant in ebx came from writing `request = REQUEST_NONE` on both paths (the
  compiler merges the stores and hoists the constant), not from a goto.
- `bool active = false; if (...) active = call(); return active;` gives the engine's `xor al, al` before the test and
  a tail jump.

## audio/audiomessage.cpp (0x107FE2B0 - 0x107FE508)

engine::AudioEmitterTriggerMessage::Apply (vftable slot 1 of the RTTI class; the messages' other members live in
another unit): finds or creates the emitter's sound, plays / stops it ("play" / "stop" with three modes) and sets
its min / max distance, pitch range and volume. The audio emitter, its sound list and sounds are only declared. Apply
is EQUIVALENT (99.4 %: the engine computes the volume parameter table pointer in eax, ours in ecx); three kept
accessor copies match. Not reproduced: 0x107FE2B0 (`lea eax, [ecx + 0x20]`) and 0x107FE2E0 (forwards
`this + 0x10` to 0x1087D7F0 of its argument).

Lessons:

- A by-value argument built with `sub esp, 8; mov ebx, esp; call ...; copy` is constructed in place by an inline
  converting constructor that itself makes the call (here a hash struct built from a core::Name); converting first
  and copying pushes the words instead.
- Float tests written `0.0f != x` / `1.0f != x` load the constant into the register (`xorps` / `movss` then
  `ucomiss reg, [mem]`); `x != 0.0f` loads the member instead.

## luascriptmanager.cpp (0x107FE510 - 0x10804EC0): done except the items under Open

engine::LuaScriptManager (RTTI; the singleton gScriptManager at 0x11284254): the engine's Lua 5.1 state and the
native functions the units register with it. The file name is a guess from the class name (no assert path). Done:
0x107FE6B0 - 0x10800843, 86 functions, all match, plus 12 kept copies (the explicitly instantiated
ScriptNameTable<Function> / ScriptNameTable<LuaCFunction> members, mapped in symbols.txt). They cover the script
allocator (ScriptBlockPool, two 0x14000-byte blocks handed out first; Function::operator new / delete, 0x107FE720 /
0x107FE760, which the Lua allocator ScriptRealloc also uses), the base script functions (print, type, traceback,
breakpoint), the registration tables, the global / registry / table accessors, the context table (event fields),
references, garbage collection and the LuaGet* / LuaPush* helpers. The Lua library itself is linked in and only
declared (`code/lua/lua.h`; its functions are mapped in symbols.txt from the engine's calls). The Vector / UID / Name
userdata helpers (0x10840770 - 0x10841040) and the service pump (0x10853890) live in other units.

The rest of the class (0x10800850 - 0x10804EC0, 183 functions) is reconstructed too: the Lua error / print handlers,
enum and C function binding, Unregister, the argument dispatcher LuaDispatch, state creation / restart / reload,
coroutines, the LuaGet*Field helpers, persistent references, the scheduled-call min-heap (Schedule, RunScheduled,
CancelScheduled*, RestoreScheduled, Update) and the constructor / destructor. About 240 functions of the unit match,
including the kept template copies (explicit instantiations of the containers, ScriptArguments::Push, Function0 /
Function1 / Method1 / Closure1 and Register / RegisterMethod).

Open:

- EQUIVALENT (same operations, different register choice, spill slot or block layout): LuaChannelPrint 0x10801220
  (the engine keeps -1 in edi), LuaDispatch 0x10801790 (frame one word larger), RestoreEnums 0x10801E00 (address
  operand order), OpenTable 0x10801F80 (block layout), LuaGetIntField 0x108020D0, LuaDumpTable 0x10802FB0 (shared
  formatting tails), DoFile 0x10803330 (path stack slot), FindFunctionSource 0x10803A60 (iterator kept in memory),
  LuaDumpTables 0x10803EA0, the constructor 0x10804230 (order of the third store of the unused array), Schedule
  0x108048E0 (spill order), RestoreScheduled 0x10804D50 (addss operand order).
- Kept copies with no source found, not reproduced: 0x10800850 (a lone ret), 0x10800A50 / A60 / AF0 / B20 / B30
  (identity constructor / empty destructor pairs), 0x10800B00 / B40 (empty allocator Free / Alloc), 0x10800B60 /
  B70 / B80 (RemoveFunction trampolines), 0x10800D30 - D50 and 0x10802850 - 0x10802880 (empty returns), 0x10800D70
  (heap ShiftUp, register allocation), 0x10802730 (PushBack for ScheduledCall) and 0x10803610 (a folded jmp thunk).
- ScriptNameTable<T>::Complete (0x107FE910 / 0x107FECC0) does not match and is left unmapped: our COMDAT copy (same
  logic, checked against the engine's) serves our callers, the engine's copies stay for the rest. The engine
  recomputes strlen(prefix) and reloads the strncmp import on every iteration of the first loop; ours hoists both.
- Small kept copies at 0x107FE510 - 0x107FE6A0, 0x107FEFC0 - 0x107FEFE0 and 0x108002E0 (a constructor initialising a
  HandleBase at +0xC): owners unknown.

Lessons:

- Unresolved Lua API functions are found by pairing our object's relocations with the call targets in the engine's
  copy of a matching function (follow the incremental link thunks); the lapi.c order of upstream Lua 5.1 confirms them.
- The LuaGet* helpers test `lua_gettop(L) == 0` and the type in two separate `if (...) return false;`: the engine
  places the false return right after the type test. One `&&` condition puts it at the end of the function (but
  LuaGetVector, whose second test is a call returning bool, matches with `&&`).
- LuaType is a switch whose cases push and `break` to one `return 1`, with the lua_typename push written both in the
  userdata fallback and in `default`: the compiler then hoists the shared `push 1; push esi` above the branch. Cases
  that `return 1` themselves do not get that.
- "ScriptFree" was Function::operator delete: ScriptNameTable<Function>::Remove's `delete entry` calls it directly.
- A by-value empty struct argument (the heap helpers' ScheduleOrder) pushes a garbage dword: declare a local
  `ScheduleOrder order;` and pass it, as free cdecl functions.
- The heap helpers SchedulePush / ScheduleRemove / ScheduleRemoveFirst are free cdecl functions around inline
  PushHeap / PopHeap; in SiftDown declare the left child before the right one.
- The constructor needs `__forceinline` closure construction (the `ClosureInPlace` tag constructors), an out-of-line
  Create for the arrays, byte-size array allocation (`operator new[](count * sizeof(T))`) and
  `memset(walkTops, 0xff, ...)`; ScriptNameTable's constructor / destructor are out of line.
- LuaDispatch only matches in control flow when the result-push tails are merged with `goto`; the state-less
  `ScriptArguments` buffer holds the pushed values (vectors per component).
- Kept template copies are made with explicit instantiations (`template class X<...>`), then mapped by byte identity
  with the automap tool; 5-byte `jmp` candidates are skipped, because the linker folds identical thunks.
- Compare the owner handle (not the reference) when cancelling the calls of one object (CancelScheduledFor).


## system/streamtrigger.cpp (0x108352B0 - 0x10836640): done (75 functions: 73 match, 2 equivalent)

engine::StreamTrigger (RTTI; reflected members neighbours, packages, hulls, boundingBox, tags): a world volume (box,
refined by StreamTriggerHull plane hulls) for the stream manager; neighbours and packages are ';'-separated name lists
held as `container::StringDynamic<AllocatorCoreStatic<12,16> >` and resolved (ResolveLinks, through the manager's
lookups 0x1082E090 / 0x1082E010) into arrays of triggers / packages. 21 class functions plus 54 kept copies (the
explicitly instantiated hull and plane arrays, the hull array's ArrayDynamicHelper, StringMemberGetSetter and the
per-member string meta type getters). Both constructors are EQUIVALENT (the reference count is cleared before the
name's address is computed in the engine, after in ours; same as SupportingLimbDefinition). Validation (2026-10-12):
free roam, long teleports, pedestrians normal.

New shared pieces: `code/container/arraydynamicstatic.h` (a partial specialisation of container::ArrayDynamic for
AllocatorCoreStatic<Heap, Align>: begin / end / capacity plus the empty allocator, 16 bytes; Create = bool, Allocate =
void, as the ArrayDynamicNew helpers), `code/content/stringmetatype.h` (StringMetaType, StringMetaTypeGetSet,
StringMemberGetSetter<C>, GetStringMemberMetaType<C, Id>), `code/engine/system/tagset.h` (TagSet, unit 0x108340A0 -
0x108351A0 not reconstructed yet), StringDynamic in `code/container/string.h`, AABB's reflection declarations.

Not mapped (no identical copy of ours): 0x108357C0 (plane AssignRange), 0x10836170 / 0x10836220 / 0x108362F0 /
0x108363A0 (hull array ShiftUp / Reserve / Insert / Insert), 0x10836590 (helper Insert), 0x10836620 (deleting
destructor). Matching notes: free function templates need `inline` to be inlined (/Ob1) — ConstructCopyAt is,
ConstructFill / AssignRange / ConstructCopiesN are not; an empty allocator argument must be a named local (a
value-initialised temporary gets a byte store); loops over a list cache its end before the loop.

## system/tagset.cpp (0x108340A0 - 0x108351A0): open, blocked on core::Name

TagSet (declared in `code/engine/system/tagset.h`): sorted core::Name tags plus an "all" flag; ToString (static
StringC buffer, tags joined), Find / Contains / Remove, Intersects / Includes (merge walks), FromString, an insert by a
comparison function (0x10834D70) and the VS2005 Dinkumware std::sort / lower_bound instances for Name* (`<algorithm>`
from the toolchain would reproduce them). Blocked: several of those instances align their frames (`and esp, -8`)
around local Name copies, which suggests core::Name holds a 64-bit member in the original (our Name is two ints, laid
out with 4-byte alignment by its users). Tried 2026-10-12: `unsigned __int64 key` breaks only the 15 camera functions
(Cinematographer keeps a Name at offset 4); the same inside `#pragma pack(push, 4)` keeps all 2376 matching. Next step:
compile TagSet's std::sort with that Name and see whether the frames get `and esp, -8`.

## audio/audiomanager.cpp (around 0x10844C00 - 0x10845800): 1 function, EQUIVALENT

engine::AudioManager (class name guessed from the system name "AudioManager" its constructor 0x108453D0 registers;
no RTTI; singleton at 0x1130E74C). Update (0x108451C0, called from the engine's real-time update with the 12-byte
UpdateContext by value) runs the audio subsystems (0x1085AB40, AudioSystem 0x108712D0), then, unless the time step is
within 1e-5 of zero, calls slot 8 with the time step on every object of an intrusive list (head / tail 0x1130E750 /
0x1130E754, node at +0x50 of the object; register / unregister are 0x108452B0 / 0x10845310), then the audio clock
(0x10AA9B50) and the emitter system (0x10878010). EQUIVALENT: the engine materialises the zero test as 0 / 1
(`setne` / `test` / `ja`) and keeps the join of each null-checked node-to-object adjustment before testing the object
(no jump threading); `Abs` as `x >= 0 ? x : -x` gives the original's `-0.0 - x`.

## render/async/private/renderglobals.cpp (0x10817A10 - 0x1081933B): every function reconstructed, 5 EQUIVALENT

The drawable table (0x1130CCC4) and the controller table (0x1130CCC8) are `HandleTable<T>` instances: slots, a lock-free
free list of index nodes (+0xC), nodes (+0x10), serials (+0x1C) and a count (+0x28); the serial counter is a static of
each instance (0x111C2E84 / 0x111C2E88, 1 .. 0xFFFE). The arrays are `SlotArray<T>` (begin, end, empty allocator). Other
globals: the render event allocator (0x1130CCDC, slots 3 / 4), the deferred deletion list and the render event queues.
Each queue is a template instance (two queues, 0x11284C60 and 0x11304C90, with identical copies of every helper): a
ring of 1 << Bits values behind a free and a ready semaphore, lock-free read / write indices and a commit structure at
+0x10 (0x10817F90: a 64-bit word with the oldest uncommitted slot in the low Bits and a bitmap of the later committed
slots above) that releases the slots that became readable. The second queue is a ring of 0x2000 values. Notes:
- The two "FATAL: Async render event queue overflowed..." asserts are OLD_ASSERT_AT with the original line numbers
  (0xA9, 0xBE).
- ExecuteRenderEvents is `while (TryPop(&queue, &event) && event != 0) event->Execute();`.
- The queue helpers are templates over `AsyncQueue<T, Bits>` (17 and 13 bits); a named `long next` read before `expected = index`
  gives the engine's registers in the index and the allocation loops.
- The thirteen one-byte functions between 0x10817B30 and 0x108185E0 are the construct / destroy helpers of the plain
  types (`ConstructRange` / `DestroyRange` / `DestroyAt`); the original keeps an out-of-line copy of each instance.
- Inlining: the element-constructing array constructor of the controller slots stays a call in the table
  constructor (declared `noinline` as an explicit specialisation); the others are `__forceinline` in the
  generic template. `ConstructRange<DrawableData>` is likewise an out-of-line specialisation.
- HandleParts index: the engine loads the handle as a word and masks it, which needs a signed `int value` member.

| Address | Name | Status | Notes |
|---|---|---|---|
| 0x10817A50 / 0x10817AD0 / 0x10817B10 / 0x10817B40 | AllocRenderEvent / FreeRenderEvent / GetRenderList / DeferDelete | match | |
| 0x10818CC0 / 0x10818DA0 | PushRenderEvent / ExecuteRenderEvents | match | |
| 0x10817D90 / 0x10817DE0 / 0x10817E30 / 0x10817E50 | queue init / shutdown (both queues) | match | the initial slot count sets the commit head and the write index; the semaphores start at ring size - n and n |
| 0x108185F0 / 0x10818650 / 0x10818620 / 0x10818680 / 0x10818C00 / 0x10818C30 / 0x10818C60 / 0x10818C90 | Reserve / Commit / TryPush / TryPop (both queues) | match | the second queue (0x11304C90) is a ring of 0x2000 values: `AsyncQueue<T, Bits>` with 17 and 13 bits |
| 0x10818D30 / 0x10818DE0 | PushRenderEventSecondary / ExecuteSecondaryRenderEvents | match | |
| 0x10817F40 / 0x108180C0 / 0x108186B0 / 0x10818720 | AllocAsyncQueueSlot / TakeAsyncQueueValue (both queues) | match | the next index is a named local (`long next = ...;`) before `expected = index;` |
| 0x10817F90 / 0x10818110 | CommitAsyncQueueSlots (both queues) | EQUIVALENT (51.0%) | the 64-bit commit state: head in the low bits, a bitmap of the later committed slots above; other registers and spill slots |
| 0x10819040 | InitRenderGlobals | EQUIVALENT (99.1%) | the store of the new event allocator and the load of its function table are swapped |
| 0x10819240 / 0x108191A0 / 0x108191F0 | ShutdownRenderGlobals / the tables' scalar deleting destructors | match | |
| 0x10818B30 | SlotArray<ControllerSlot> constructor | EQUIVALENT (98.9%) | the branch for an empty range goes to the second of two identical epilogue copies, the original's to the first |
| 0x10818E20 | HandleTable<DrawableData> constructor | EQUIVALENT (81.7%) | the block clearing the first array after a failed allocation sits behind a jump after the construct call (the original puts it after the second array's success branch); one operand order of an address |
| 0x108182C0 / 0x108183E0 | HandleTable<DrawableData / ControllerSlot>::Alloc | match | the node's next pointer is a named local read before `expected = node;` |


## engine/physics/physicsmanager.cpp (0x107E2440 - 0x107E7A00), started

The unit's assert path (`..\..\..\code\engine\physics\physicsmanager.cpp`, lines 0x794 - 0xA4F) names it; its
functions run from 0x107E2440 (right after `engine::MasterTable`'s constructor) to 0x107E75F0 (2598 bytes) and the
unit registers the `pm_*` console commands (0x107E6F20). One source file holds everything in the range: the
collision messages, the shared query buffers and the manager's Lua commands share one translation unit (the small
class at 0x107E2BF0 that reads the pad axes is constructed by 0x107E3710, so the "climbing" input map is part of
it too). 84 functions match so far, in address order:

- the eight collision messages (RTTI): `CollisionBrokeringMessage` (type 4), `CollisionResponseMessage` (type 5),
  `BatchedRayCastMessage` / `BatchedRayCastHitMessage` / `BatchedShapeCastMessage` / `BatchedShapeCastHitMessage`
  (type 3, ids 1 - 4), `PhysicsFixupUnsolvedConstraintsMessage` (id 0x1D) and
  `PhysicsFixupPoweredConstraintsMessage` (id 0x1E) - constructors and destructors. The batched cast payloads are
  **separate scalar arguments**, not a by-value struct: a struct argument schedules one store differently (the
  engine stores the first word with the others, ours after the vftable) and never matches.
- the three shared query buffers and their locks (`RayHitBufferLock` 0x107E6CD0 / 0x107E3C20 / 0x107E3C30, plus
  `HitIndexBufferLock` and `CollisionBufferLock` at 0x107E6CF0 / 0x107E6D10 - both names are guesses). The locks
  hold **no data**: the buffers are file-scope variables, which is what makes the engine address them absolutely
  (`arg = ctx ? ctx : (Type*)field` would use `this`). The three array types are `{begin, end, capacity}`.
  `engine::RayHitBufferLock` is declared in `code/ravenphysics/context.h` because supportinglimb.cpp uses it.
- the `pm_` console commands 0x107E3F20 - 0x107E57E0: `pm_DrawInertia`, `pm_DrawObjectUIDs`, `pm_TrackAABB`,
  `pm_SetSolverIterations`, `pm_ListStaticObjects`, `pm_ListMovableObjects`, `pm_ListAwakePhysicsObjects`,
  `pm_ListAsleepObjects`, `pm_ListSelectedObjects`, `pm_ListPhysicsObjects`, `pm_ListTriggerObjects`,
  `pm_ListObjects`, `pm_Substeps`, plus the frame counter and the update flag under them.
- the interlocked helpers `AtomicIncrement` / `AtomicDecrement` (0x107E3790 / 0x107E37A0) - **`__fastcall`**, the
  pointer arrives in ecx.
- the messages' eight scalar deleting destructors (0x107E4810 - 0x107E48F0). A destructor written out of line in the
  cpp is *not* inlined into `??_G` under `/Ob1` (ours called `??1` and came out 30 bytes), so the empty destructors
  of the six batched/collision messages are marked `inline`: their out-of-line copies at 0x107E38A0 - 0x107E3A70 stay
  byte-identical and `??_G` expands them the way the original does. The two PhysicsFixup messages declare no
  destructor at all, so theirs is implicit; the original's linker folded the two identical copies into one (the eight
  message classes leave seven seven-byte destructors), which is also why 0x107E3AB0 carries the two classes' shared
  code and why every one of these functions stores the same vftable address.
- the unit's four `container::ArrayDynamicNew` instantiations, as a commented `// FUNCTION:` block over the explicit
  `template class` statements: `unsigned int`, `engine::CollisionItem` and `engine::ConstraintItem` (0x1C bytes,
  copied as seven words - the element sizes come from the code, the names are guesses) and `engine::CollisionPair`
  (0x70 bytes). They give 0x107E4340 - 0x107E4770 and 0x107E5830 - 0x107E5930 (Begin / End / Size / operator[] /
  Create / Allocate / PushBack / ConstructAt), and their `Free` / `Clear` / destructors at 0x107E69C0 - 0x107E6B60
  and 0x107E70E0 - 0x107E7100. `container::ArrayDynamicNew` gained an `End()` (the original's class has one; the
  array's users here call it). Five `Free` copies stand for four element types, so a fifth element type is still
  unidentified and 0x107E6AE0 is left unclaimed.
- `Erase` is **not** this class's: the original's (0x107E6AA0 / 0x107E6B10) walks the range through a copy loop, ours
  shifts one element at a time (19 %).
- the `pm_` registration 0x107E6F20 (`RegisterPhysicsCommands`): it registers all twenty commands, so the unit needs
  the `Function` wrappers the header had only for zero and one argument. `function.h` gained `Function0<void>`,
  `Function2`, `Function3`, `Function4` and their `void` forms, and `Register` gained the two-, three- and
  four-argument overloads; the unit then emits the four-argument wrapper's constructor, `Call` and `Invoke`
  (0x107E59C0 / 0x107E5A30 / 0x107E5A70) and the `Register` copy 0x107E6B70 by itself. The 0- and 1-argument
  `Register` copies are calls to another unit (0x10280020 / 0x10374950), which `symbols.txt` maps.
- the uid table, `ravenphysics::KeyTable` (name guess; the engine's copy has no RTTI): `Find` 0x107E6BC0,
  `FindFrom` 0x107E5AB0, `FindAfter` 0x107E6C00 and `Create` 0x107E7120 match, and `Init` (0x106883B0, another
  unit) is mapped. The layout is `next / slotCount / buckets / bucketCount / keys / count / capacity / order /
  orderCount / orderCapacity`, all of it cut out of the scratch stack when the table is created. **The chain walk
  is written with an early `return slot`**, not a `break` (that is the whole difference between 0x107E5AB0 and
  0x107E6C00's shape): `while (slot != 0xFFFF) { if (keys[slot] == key) return slot; slot = next[slot]; }`.
- the object lookup by id 0x107E4E60 (thiscall on an `ObjectList`, three stack arguments: the id, and the two
  outputs - the physics object and the collision object), which fills the layout the `pm_` listings need:
  object +0x22 (16-bit id), +0x3E (flags, bit 3 tested), +0x5C (16-bit count), +0x54 (pointer array), and the
  collision objects' own id at +0x4A. 0x107E4F00 is the same lookup over `movableObjects` (the context at +0x1C)
  then `staticObjects` (+0x14) - **it takes its two outputs in `esi`/`edi`**, a link-time code generation
  convention like `AtomicExchange`'s, so it and its callers (0x107E5770 and the other listings) cannot be written
  in C++ as they are.

NONMATCHING:

- 0x107E37B0 AtomicExchange: the engine's copy takes the value in `eax` (a link-time code generation convention),
  ours in `edx`; 60 %.
- 0x107E6C40 KeyTable::Insert: the same instructions in the same order, but the new slot and the old chain head come
  out in the other pair of registers (`eax`/`esi` swapped); 87 %.
- 0x107E4010 pm_LogCollisions: the engine materialises the `"collisionLog.txt"` argument in its stack slot *after*
  pushing the other eight (a wildcard `push ecx`, then `mov eax, esp`, then the literal into the slot); ours pushes
  the literal directly. The same shape blocks `LuaScriptManager::DoFile` in another unit; 53 %.
- 0x107E3F90 UpdateCollisionLog: the engine issues the `gCollisionLogState = 0` store between the two loads that
  prepare the `Release` call (`mov ecx,[file]; mov eax,[ecx]; mov edx,[eax+4]; mov [state],0; call edx`), ours issues
  it right after the pointer load; 90 %.
- The collision log's globals **are** now known and written down: state 0x11283594, frames left 0x11283598, the file
  0x1128359C, the report-once flag 0x111BC613 (the ` Report(0, " Pre ", ...)` in 0x107E3F90 is the original's). The
  line in that report is 0x9E1 and the format `Logging collisions frame %d.`.

Not done (owners or layouts not recovered yet; the reasons are what blocks them, not just "unknown"):

- 0x107E37B0, 0x107E37C0 - 0x107E3800 (a `BitField<unsigned short>` read at +2, three `mov eax,ecx` copies and a
  virtual dispatch guarded by a float member at +0x10), 0x107E3830 - 0x107E3860, 0x107E3AC0 - 0x107E3B00,
  0x107E3B60 / 0x107E3B70, 0x107E3B80 / 0x107E3BC0, 0x107E3DA0, 0x107E45B0 / 0x107E4630, 0x107E45C0 / 0x107E4640 /
  0x107E47E0: accessors and one- and three-byte stubs of classes the unit's messages and manager own (member offsets
  0x14, 0x1C, 0x70, 0xC0, 0xC2, 0xE0). The owner of the three-byte `mov eax,ecx` copies is not recoverable from the
  code alone and no assert or RTTI names it.
- 0x107E3D00 / 0x107E3D10, 0x107E3C00 / 0x107E3CB0 / 0x107E3CD0, 0x107E3D60: ravenphysics::Context wrappers (the
  callees at 0x10656660 / 0x10656670 / 0x10659D50 are not named yet, so the calls cannot be declared) and a
  constructor whose members are still unknown.
- 0x107E3DB0, 0x107E3DF0, 0x107E3EA0, 0x107E3ED0, 0x107E3F90 / 0x107E4010 (the collision log: it opens
  `collisionLog.txt` through `core::OpenFile` and logs with `core::Report`, but the log's reader/writer object and the
  `Logging collisions frame %d.` frame counter's owner are not placed), 0x107E40B0 (`pm_Help`), the rest of the
  container helpers (see above), `ListObjects` 0x107E4F40, 0x107E4E10 / 0x107E4E60 / 0x107E4F00 (the object lookup
  by uid and by collision-object index - they need the ravenphysics object layout at 0x22 / 0x3c / 0x3e / 0x54 /
  0x5c), 0x107E4910 / 0x107E49B0 / 0x107E49E0 / 0x107E4A50 (the uid lookup loops over the console's token tables at
  0x111BC2EC / 0x111BC2FC), 0x107E52A0 - 0x107E6B70 (the remaining list commands, the `Function4` script wrapper
  0x107E59C0 and the constraint dumps) and 0x107E6C40 - 0x107E75F0 (the uid hash table - `Insert` 0x107E6C40,
  `Find` 0x107E6BC0 / 0x107E6C00, `Create` 0x107E7180, `Destroy` 0x107E6D30, the `pm_` registration 0x107E6F20 and
  `Update` 0x107E75F0).
- 0x107E2BF0 and its 0x107E24B0 - 0x107E3710 neighbours (the pad-driven "climbing"/"wall_run" input map). It is one
  coherent block: a 12-byte state machine (0x107E2490 / 0x107E24B0 / 0x107E2580), an 8-byte and a 16-byte sibling
  (0x107E25C0 - 0x107E2640), the axis readers 0x107E26A0 - 0x107E2840, the map's arrays of those states
  (0x107E2B40 / 0x107E31C0 / 0x107E3530 - 0x107E3710, 0xC-byte elements) and the update 0x107E3290, which walks a
  0x18-byte-stride binding table with rows at +8, +0x18, +0x28, +0x38, +0x48 and 0x28-byte rows at +0x58. What blocks
  it is the object behind `+0x2b8` (its axis table at +0x58, button words at +0x100 and float pairs at +0x1a8 are
  read by every axis reader) - it is a controller/entity the unit does not define.
- Not reachable at all: 0x107E58A0 / 0x107E58F0, five-byte `jmp` thunks of 0x107E4550 / 0x107E45D0 (the original's
  incremental link table leaves a copy at each call site); our linker emits no such thunk, so they cannot be matched.

Added later (sn-anim): the two global singly linked lists of `ravenphysics::PhysicsContextCallBack` (new header
`code/ravenphysics/callback.h`: an abstract class with one pure virtual and `next` at +4) with `PushCallback` /
`EraseCallback` (0x107E3DB0 / 0x107E3DF0, non-static: the engine passes their arguments on the stack) and the four
Add/Remove Pre/PostStepCallback entry points (0x107E4D90 - 0x107E4DF0), `KeyTable::GetBucket` (0x107E4990),
`ResetPlacement` / `SetPlacementPosition` / `SetCollisionModeInBox` (0x107E3D00 / 0x107E3D10 / 0x107E4E10). The rest
of the range stays as listed above: the 0x107E3F90 - 0x107E4010 collision log (owner object unknown), the dead
`ArrayDynamicNew` members, the pad-input cluster and the routines with register conventions whose owners are not
recoverable.

Shared headers touched: `code/ravenphysics/context.h` (the query buffer lock, `Context::SetSolverIterations`, the
`ObjectList` members at 0x14 / 0x1C and `Context::unknown0`) and `code/container/arraydynamicnew.h` (`End`).

## render/async/private/drawable.cpp (0x107E8020 - 0x107EE322): 288 annotated functions, 274 match, 14 EQUIVALENT

engine::render::Drawable is the game thread's handle to a render-thread drawable (a 16-bit slot index and the slot's
16-bit serial). Its methods queue render events (`QueueRenderEvent`, renderevent.h) whose "Do" function runs on the
render thread; the unit is, in address order: the Do functions (static, address taken by the event), the methods that
read the render object directly, the explicit instantiations of the event classes (constructor and `Execute` each),
the `QueueRenderEvent` instantiations, then the queueing methods.
- A `RenderEventN` instance frees itself with `delete this` (the base class's operator delete is `FreeRenderEvent`).
  The classes with a member that has a destructor (the pddi shader input data, the names) therefore get an implicit
  destructor and a scalar deleting destructor of their own, and their `Execute` expands the destructor
  (0x107EB570 and the nine like it).
- `core::Name<CaseSensitiveKey>` is laid out at a multiple of 8 inside the events (`EventMember` in renderevent.h
  pads it); 4-byte names (`Name<CaseInsensitiveKey32>`) have an empty user destructor, which is what makes their
  event classes non-trivial. `GetCurrentDrawable` (0x20 bytes) has a trailing member for the same reason.
- The shader parameter events and one of the two modifier events go through the second queue (0x10818D30,
  `QueueRenderEventSecondary`); `PushRenderEventSecondary` is declared in renderevent.h and not reconstructed.
- Kept copies: members of header classes are compiled after their callers, so the callers cannot rely on the
  registers the copy leaves alone (`EffectBiases`' copy constructor is defined in the struct for that reason; defined
  in the cpp the event constructor keeps `this` in edx). The copies the unit keeps are annotated in blocks at the end
  of the cpp (pure3d accessors, the particle state setters, name destructors, the event destructors).
- Matching notes for the Do functions: the loop idiom is `unsigned int i = 0; unsigned int count = parts.Size();
  for (; i < count; ...)` (the zero is loaded before the division) or a plain `for` for the others; parts are read
  through named `PartRef` locals (`PartRef part(impl, i); part->state`, a second named local for the state when the
  type test and the access are separate); `FindSegment` goes into a local before the call that uses it; a second
  exit that frees nothing is an early `return` (the heap scope is destroyed in two places); the playback frame
  clamps are local copies (`float startFrame = frame; if (0 > startFrame) { float wrapped = ...; startFrame = 0 > wrapped
  ? 0 : wrapped; }`).
- EQUIVALENT: DoShareBindings (the part counts are compared the other way round), DoPlayPartAnimation (frame
  layout), the four DoSetBinding functions (the part's address is folded into the load of the binding), DoCreateInstance
  (the original expands `CreateOptions(bool)` in place), DoCreateInstanceWithOptions (the failed lookups share one
  exit), DoSetBiasUnknown (register rotation), SetJointMatrices (conditional move for the count clamp),
  RenderEvent2<Drawable, Matrix>::Execute and Drawable::SetTransformQueued (the original copies the matrix argument
  with the compiler's vector copy-constructor helper), Drawable::LoadTexture (evaluation order of the lookup; its two
  last parameters are passed on to the uploader), ParticleSystemState::SetBias (kept copy; the original converts the
  channels with the x87 truncation and merges them with xor masks).
- Not annotated: 0x107E80F0 (a one-byte empty function whose symbol name is already taken by the copy in
  streamtrigger.cpp) and 0x107E8B50 (the size of a 16-byte-element array of the drawable at +0xA4, no user in the
  unit).

## render/async/private/parameterinterpolator.cpp (0x108C02D0 - 0x108C04D6): 5 functions match, 1 NONMATCHING

engine::render::ParameterInterpolatorPool (name guessed; the file is named by the assert in `Alloc` at 0x108C03B0):
the pool the render parameters are interpolated between two frames out of. It is one `operator new[]` block holding
the 0x40-byte `engine::render::ParameterInterpolatorTypeless` objects, then a free list of their
addresses, then one "in use" byte per slot (`mMemory` +0, `mCapacity` +4, `mUsed` +8, `mUsedFlags` +0xC, `mFree`
+0x10; the member names are guesses). `mMemory` is a `char*` on purpose: `delete[]` of a pointer to the polymorphic
slot type would run the slot destructors and match neither the constructor's `??_U` nor the destructor's plain
`??_V` call.
- 0x108C02D0 fills the free list so that slot *i* is the *i*-th object of the block; writing the offset as a loop
  variable (`offset += 0x40` before the loop) leaves the initialization before the loop's top test and the function
  does not match — `mMemory + i * 0x40` inside the loop gives the original's strength-reduced induction variable.
- 0x108C0350 (`ReleaseAll`) and 0x108C0440 (`Release`) walk the *objects* (`mMemory + i * 0x40`), not the free list;
  only `Alloc` (0x108C03B0) pops `mFree[mUsed]`, and the update walk pushes the finished slots back with it.
- The assert in `Alloc` is a `core::Report(1, "Engine", __FILE__, 0x5f, 0, "...", 0)` behind a file-local
  `static bool` that a "3" answer switches off; the message is the original's.
- 0x108C0420 is `ParameterInterpolatorTypeless::GetName`, the copy constructor of the name at +0x18 through the
  hidden return pointer. The original inlines it into `Release`, but writing it out of line in the cpp matches the
  original's own copy exactly (and `Release` does not match either way).
- slot *i*'s id is the int at +0x20 and its name (`core::Name<core::CaseSensitiveKey>`) at +0x18.
- NONMATCHING: 0x108C0440 Release (`?Release@ParameterInterpolatorPool...QQAEXHABV?$Name...`): register allocation,
  96 %, the original holds the id in eax and the name copy's source in ecx where ours picks ecx and edx, every
  instruction otherwise identical (swapping the `==` operands makes it 95 %).
- Not done: 0x108C02B0 (`return *(int*)(this + 0x30)`) and 0x108C02C0 (`this + 0x20`): two four-byte accessors
  between the previous unit and the pool constructor. The unit before this one ends with 0x108C02C4 and this one
  starts at 0x108C02D0, so they are most likely its tail rather than the pool's slot accessors.

The four units of the block after deferreddeletion.cpp (the only one of them whose file name survives in the binary
is this one, in the `Alloc` assert at 0x108C03B0; the boundaries are where the code and the `.data`/`.rdata` order
agree, see `tools/rtti.py`'s vftable order):

| Range | Unit | Contents |
|---|---|---|
| 0x108BC810 - 0x108BEF7F | `code/engine/render/letterboxrenderpass.cpp` (0x108BC810 - 0x108BD880) and `code/engine/motiontrail.cpp` (0x108BD890 - 0x108BEF7F) - both file names are guesses | `engine::render::LetterboxRenderPass`, `pure3d::DebugObjectManager` / `debugoverlay::DebugSelectionManager`, `engine::MotionTrail`, `MotionTrailCreator`, `MotionTrailState` (their six vftables are consecutive in `.rdata`) |
| 0x108BEF80 - 0x108C02C4 | not placed (55 functions) | `engine::OnlineManager` (0x108BEF80 / 0x108BEFA0 / 0x108BEFC0 register it and its peers), replay / CRC / desync reporting (0x108BF030 reads `ReplayMode`, `recordCRC`, `DesyncHunt`; 0x108BFD30 dumps a controller desync) |
| 0x108C02D0 - 0x108C04D9 | this unit (6 functions) | the pool |
| 0x108C04E0 - past 0x108C1000 | `code/engine/fmv/fmvsubtitlemanager.cpp` (not started) | `engine::FmvSubtitleManager` and its `SubTitleEnty` (0x10C bytes), the `content::ArrayDynamic` / `ArrayDynamicHelper` copies |

### What the last session did in these four units (and what is left)

`render/letterboxrenderpass.cpp` (7 functions match, 1 NONMATCHING, ~53 not done):

- Matched: 0x108BC810 `Letterbox::SetEnabled` (the byte at +0x16), 0x108BCB30 `Letterbox::GetAspectRatio` (a tail call
  into `engine::gDisplay`) and 0x108BCDE0 `DebugSelectionManager::DebugSelectionManager`. 0x108BC8C0
  `DebugObjectManager::DebugObjectManager` is defined in the class body (the derived constructor inlines it, which is
  what the original does), so it is emitted and objcmp reports it 100 % but it carries no annotation and is not counted.
- `engine::render::Letterbox` (the class owning the pool, the two fade helpers and the pass) is only partly placed: the
  constructor 0x108BD150, the destructor 0x108BCBE0 and the update 0x108BCC50 need the fade helper class
  (`108FD0A0` - `108FD8C0`, another unit, not reconstructed), `1074DF40` / `1074E8F0`, `10754A40` (`Context::FindPass`
  by name), `108BD0D0` (the pass factory), `106DF460`, `10710AA0` and `10A9B7B0` named first.
- `LetterboxRenderPass::LetterboxRenderPass` (0x108BC830) takes one four-byte argument that it pushes straight into
  0x10754A70; that function copies a `core::Name` from +8, a byte from +0x10 and a dword from +0x14, so it is **not**
  `Pass::Pass(const Pass&)` as the class layout suggests and its parameter type is still unknown.
- 0x108BC860 and 0x108BC880 are the compiler's scalar deleting destructors of the fade helper and of something holding
  the pool at +0; they call `~FadeHelper` (0x108FD8B0) and `~ParameterInterpolatorPool` (0x108C0340) with `this`
  unchanged, so neither class can be polymorphic. How the original emits them is unsolved.
- Not done, unplaced: 0x108BC820 / 0x108BC8A0 (1-byte `ret`), 0x108BCA00 (`ret 4`), 0x108BCDF0 (`ret 8`),
  0x108BCB60 (`return this->unknown14`), 0x108BCB70 / 0x108BCEA0 (`return *(void**)this + 0x10`), 0x108BCE80,
  0x108BCEB0 and 0x108BCB80 are `container::Map`-style iterator helpers of a container this unit instantiates (the
  key and value types are still unknown), 0x108BD470 (`al = this+0x68`), 0x108BD480 / 0x108BD8D0 / 0x108BDC70
  (`mov eax,ecx; ret`, three classes' "return this" accessors), 0x108BD900 (a four-byte swap), 0x108BCB30's
  neighbours 0x108BD2C0 - 0x108BD740 (a class with a tree, floats at +0x5c - +0x68 and a 0xD0-byte copy at
  0x108BD490).

`engine/motiontrail.cpp` (4 functions match, 0 nonmatching, ~18 not done): 0x108BD960 `MotionTrailCreator`'s
constructor (the vftable and the -1 at +4) and 0x108BD8A0 / 0x108BD920 / 0x108BD940, the two `MotionTrail` buffers
(six floats at +0x1C and four at +0x34; the getter at 0x108BD8A0 writes the second three-float vector first, and
naming the destination pointer `second = values + 3` is what makes the original's `mov eax, [esp+4]` come before its
first `fld`).
- `MotionTrail`'s own constructor 0x108BD890 stores the vftable and tail-jumps to 0x106F2FB0, which a base constructor
  could not survive: the base is not `pure3d::Primitive`'s constructor, or it is not a base constructor at all. The
  base is unplaced, and the class is declared in motiontrail.h without its bases for that reason.
- 0x108BD970 (749 bytes), 0x108BDCA0 (1189), 0x108BE810 (1350), 0x108BED80 (464) and 0x108BE4A0 (517) are the unit's
  bulk and are not started; 0x108BD8D0 / 0x108BDC70 (`mov eax,ecx; ret`) and 0x108BD900 (a four-byte swap) are
  unplaced.

## render/async/private/deferreddeletion.cpp (0x108BC250 - 0x108BC7B0): 5 functions match, 15 kept copies

engine::render::DeferredDeletionManager (the name is in the overflow assert; the singleton is the pointer at
0x1130CCCC): a ring of 3200 reference-counted objects (`mRefCountedItems`, `mHead`, `mTail` are the assert texts) that
the game thread is done with. `Add` (0x108BC640) stamps an entity with the next frame and keeps a reference;
`Process` (0x108BC400, once per frame, called through 0x10817AF0) releases the items whose frame has passed and
returns the frame counter it increments; `Clear` (0x108BC550) releases everything and runs when the ring overflows.
Layout: count at +0, frame at +4, head at +8, tail at +0xC, the items (frame, reference) from +0x10. All
counters are accessed interlocked (`_InterlockedAnd(&x, -1)` is the atomic read).
- The helper classes (AtomicInt, RingIndex<3200>, RefPtr<pure3d::RefCounted>, RefCountedItem, FixedArray<T, N>) are
  in deferreddeletion.h; the 15 small functions between and after the real ones are their members, kept as separate
  code (annotated at the end of the cpp). `Load` must be `inline` (the project inlines only inline functions at /Ob1),
  and `return frame->ExchangeAdd(1)` through a local pointer gives the original's `add edi, 4` before `mov eax, 1`.
- RefPtr::operator= compares first (`if (mPointer != object)`) and returns the pointer after the block.
- Not reproduced: 0x108BC250 (an atomic read taking the address in edx, `this` unused) and 0x108BC290 (`xchg [ecx],
  eax` with the value already in eax), two unreferenced leftovers.
- renderglobals.cpp still lacks the callers of this class: 0x10817AF0 (Process), the constructor / destructor calls
  at 0x108190B4 / 0x108179B3 / 0x1081924D.

## render/letterboxrenderpass.cpp (0x108BC810 - 0x108BD880) and engine/motiontrail.cpp (0x108BD890 - 0x108BEF7F): 0 functions, not started

The two units between deferreddeletion.cpp and the OnlineManager block. The split is the one the previous session
recorded (0x108BC810 - 0x108BEF7F), cut at 0x108BD890 where the MotionTrail constructors start; the file names are
guesses (the only vftables the block carries are `engine::render::LetterboxRenderPass`,
`pure3d::DebugObjectManager`, `debugoverlay::DebugSelectionManager`, `engine::MotionTrail`,
`engine::MotionTrailCreator` and `engine::MotionTrailState`, in that order in `.rdata`, and one unit's namespaces
say nothing about its file).

What the two units are, from their code:

- 0x108BC810 - 0x108BD880: `engine::render::LetterboxRenderPass` (a pure3d::Pass, 0xb0 bytes, created by the
  factory 0x108BD0D0 through `new` + the pass name "LetterboxRenderPass"), `pure3d::DebugObjectManager` and
  `debugoverlay::DebugSelectionManager` (both trivial: their constructors only store their vftable), a screen-fade
  helper class (0x38 bytes: a colour, a `pure3d::Shader` named "unlit" at +0x10 and two
  `engine::render::ParameterInterpolator<float>` at +0x14 and +0x24; its methods are 0x108FD0A0 - 0x108FD8C0, in
  another unit) and the class that owns them (constructor 0x108BD150, destructor 0x108BCBE0: `core::Name` at +0x38,
  a `ParameterInterpolatorPool` of 0x20 slots at +8, two fade helpers at +0x2C / +0x30, a direct-3D view at +0x10,
  the letterbox pass looked up by name, `sub_1074DF40` / `sub_1074E8F0` handles at +4 / +0xC; the bool at +0x16
  switches it on, +0x18 the letterbox). 0x108BC8E0 fills the global viewport rect at 0x113184F4 from
  `pure3d::pddi` (`GetUnknown`/`GetWidth`-style entries 0x20 / 0x21 / 0x24 / 0x25 / 0x26 / 0x27, each scaled by
  1/1024).
- 0x108BD890 - 0x108BEF7F: `engine::MotionTrail` (a pure3d::Primitive), `MotionTrailCreator` (an
  engine::render::DrawableCreator) and `MotionTrailState` (a pure3d::PrimitiveState); the factory 0x108BED80 builds
  a MotionTrail out of an engine::render::Drawable and a stream package.
- The three little functions at 0x108BC850 (`jmp ??1Pass@pure3d@@UAE@XZ`), 0x108BC880 and 0x108BC8B0 are
  linker/compiler leftovers: 0x108BC850 is a COMDAT-folded jump and cannot be reproduced from source.

## engine/online/onlinemanager.cpp (0x108BEF80 - 0x108C02C4): 2 functions match, 0 nonmatching

The unit between the two above and parameterinterpolator.cpp; the file name is a guess (the block's only names are
the strings `engine::OnlineManager`, `ConsoleManagerPeer` and `ChannelManager` its registration functions pass to
0x108EC860, which is the metaclass/factory registration the other manager units use). Contents: the manager
constructor 0x108BF160 and its vftable slot 0x108BF880, an update that walks the peer list (0x108BF1B0), the
replay/CRC reporting (`ReplayMode`, `recordCRC`, `DesyncHunt` are looked up by name at 0x108BF030; 0x108BFD30 is
1382 bytes and dumps two controller states), and the command line option `HardwareProfile`.
- 0x108BEF80 / 0x108BEFA0 / 0x108BEFC0 are NOT registrations: they are the class-specific `operator new` of
  engine::OnlineManager, engine::ConsoleManagerPeer and ChannelManager (21 bytes each), and they all forward to the
  same helper 0x108EC860 with the selector 0 and their own class name as the third argument. The helper picks the
  heap: 0 is heap 0x81, 2 is heap 0x82 and 1 is the heap the global at 0x111E2060 holds (that is the value the
  third and fourth branches use), so `OnlineManager::operator new` and `ConsoleManagerPeer::operator new` are
  reconstructed in `engine/onlinemanager.cpp` against the helper, which `symbols.txt` names
  `engine::AllocateManagerObject`.
- 0x108BEFC0 is the same for ChannelManager, and is not done: the class has no RTTI entry, so neither its
  namespace nor its mangled name is known.
- The unit's own members: `OnlineManager` is 0x98 bytes (its constructor 0x108BF160 zeroes +0x70 / +0x74 / +0x78,
  builds a `core::Time` at +0x84 out of (0, 0), and installs the vftable 0x10E7DE58; the count at +0x94);
  its deleting destructor is 0x108BF880 and goes through 0x108BF690 and 0x10836820.
- `OnlineManager::OnlineManager` (0x108BF160, 50 bytes) itself is understood and ready to write: base constructor
  0x108372E0, then the vftable, then +0x70 / +0x74 / +0x78 = 0, `core::Time` (0, 0) at +0x84, then +0x94 = 0. It
  stores one vptr, so the class is one polymorphic chain (`engine::ISimulationDriver` over
  `engine::SimulationDriverTimeData`, the order the RTTI gives) and the ten slots of that chain have to be declared
  for it to compile; nothing in `src/` shows them yet (`engine::ISimulationDriver` and
  `engine::SimulationDriverTimeData` do not exist), so the constructor is not written.
- The unit's small pieces, none of which needs more than the class above: 0x108BEFF0 (`return this->unknown6C`),
  0x108BF4A0 (a virtual call at +0x78), 0x108BF4B0 (+0x80 = 0, then 0x1063CCE0), 0x108BF5B0 (0x10836990, then a
  virtual call at +0x78), 0x108BF5D0 / 0x108BFBD0 / 0x108BFCC0 (1-byte `ret`), 0x108BFBA0 / 0x108BFBB0
  (`return 0`), 0x108BFBC0 (+0x20 = 0) and 0x108BFCD0 (`return param_2`). 0x108BEFE0 and 0x108BF1A0 are not
  functions of the unit: both are 5-byte COMDAT-folded jumps to 0x1063AC00.
- The replay/CRC reporter is a second class in the unit: 0x108BF030 is its default constructor (a config struct with
  0x40 at +4, 0x32000 at +8, 0x1400 at +0xC, 0x32 at +0x10, 0x25800 at +0x14 when `ReplayMode` / `recordCRC` /
  `DesyncHunt` are on, 0x81 at +0x1C, 3 at +0x24, 10 at +0x2C, 100 at +0x30, 0x1E at +0x38, 1 at +0x3C, 0x3C at
  +0x44, 0x32 at +0x48 and 0x1E at +0x4C), 0x108BF000 is its "all the bits of +0x28 are set" test and 0x108BF020
  its +4 getter. None of the three is written: the struct has no name and no RTTI.
- The last two functions of the block, 0x108C02B0 (`return this->unknown30`) and 0x108C02C0
  (`return this->unknown20`), are still unplaced; the desync dump 0x108BFD30 (1382 bytes) is the class they most
  likely belong to.

## engine/fmv/fmvsubtitlemanager.cpp (0x108C04E0 - 0x108C1480): 51 functions match, 0 nonmatching

engine::FmvSubtitleManager (the name is the string its own reflection carries): the subtitles of a full-motion video.
The unit is the one after parameterinterpolator.cpp in `.text` and the file name comes from
`docs/original_tree.md`; the manager is a content library object (content::MetaLoadObject) whose single reflected
member is the element array `subtitles`.
- FmvSubtitleManager::SubTitleEnty is 0x10C bytes: `char subtitleId[0x100]` at +0 (a content::StringMetaType
  member, capacity 0x100), `float startTime` at +0x100, `float endTime` at +0x104 and a text handle at +0x108. It
  is a plain struct (no vtable): its copy is the compiler's 0x10C-byte dword loop.
- `subtitles` sits at +8 of the manager (right after IRefCount's vtable and count) and is a
  `container::ArrayDynamic<SubTitleEnty, container::AllocatorNew>`; its members are the ones this unit
  instantiates (Create, Allocate, Size, Capacity, operator[] twice, Clear, Free, Erase, ShiftUp, Reserve, Insert).
  The class is a partial specialisation of the primary template in `arraydynamic.h`, whose members (the camera
  director's instantiation) differ, so it lives in `code/container/arraydynamicallocatornew.h` under the same name
  and with the same mangling as the original's.
- The instance the array is reflected through (`ArrayDynamicHelper<...>`) has its own copy here, because its
  `Insert` inserts `Default()` — the static element at 0x113185E0 — and not a local static: the explicit
  specialisation is in `fmvsubtitlemanager.h`. Note the helper's vtable puts `Get` at slot 1 and `GetConst` at
  slot 2 (the two bodies are identical, only the vtable tells them apart).
- The reflection is built in function-local statics, so the unit's `.data` is the SubTitleEnty's ClassInfo
  (0x11318594), the manager's (0x113185A4), the two PrimitiveMetaType<float> of its float members (0x113185C4 /
  0x113185D0), the default element (0x113185E0), the metabject tables and the two meta types. Their guard dwords
  sit right after each object; a ClassInfo is 0xC bytes and a MetaType-derived static 8 or 0xC.
- The `Id` the two `GetMemberPrimitiveMetaType<SubTitleEnty, float, Id>` are told apart by is 32 and 35 (the values
  the unit's mangled names carry), not `__LINE__`: writing `__LINE__` makes the name move with every edit.
- 0x108C0DC0 (`content::GetClassMetaType<SubTitleEnty>`) and 0x108C0E10 (`content::GetArrayDynamicMetaType`) are
  the metatype.h templates; the manager's own reflection (GetClassInfo / GetMembers) is *not* in this unit — it
  starts past 0x108C1000 — so the two are emitted here through an explicit instantiation.
- 0x108C0E60 / 0x108C0EA0 are the same `LoadInventory::Find<T>(const char*)` for FmvSubtitleManager and
  engine::StreamPackage: `DynamicCaster<T>` on the stack, `ObjectName(name, 1)`, then virtual slot 5
  (`FindObject`) with recursive = true. The template was added to `code/content/loadinventory.h` and both
  instantiations are explicit.

The tail of the unit (0x108C1020 - 0x108C1480) is the manager itself, reconstructed in the same file:
- `GetMembers` (0x108C1020, one member `subtitleList`, the array meta type of `GetClassMetaType<SubTitleEnty>()` with
  the code "p"), `Update(float)` (0x108C0CD0: shows a subtitle through `SubtitleOptions::Show` when
  start <= time < end, takes it down through `Hide` once the end has passed), `Reset` (0x108C10B0: hides every text
  object, then empties the array), the constructor (0x108C1340: `subtitles.Create(10)`), the destructor (0x108C1390:
  Reset, then the array's destructor expanded inline) and the deleting destructor (0x108C1480).
- 0x108C0BB0 is the unit's file-local helper (`static GetMovieName(path)`: the text between the last separator and
  `.bik` / `.rmv`, as a `StringC<256>` returned in edi); 0x108C1130 / 0x108C1210 call it and look the manager (resp.
  the stream package) up by that name. The asserts of 0x108C1130 name `pkg` (line 0x7A) and `inventory` (0x7E).
- `ArrayDynamicHelper::Default` must be an inline static of the class body (the engine inlines it into `Insert`,
  0x108C13C0, and keeps an out-of-line copy, 0x108C08A0).
- `container::StringC<N>` got the two constructors the unit uses (from text, copy) and `container::String::FindLast`
  its two-argument form (0x108C04E0, an inline function whose out-of-line copy the unit keeps).
- `SubtitleOptions` (the object at 0x11316A58) moved from fmvplayer.cpp to `code/engine/fmv/subtitleoptions.h`;
  0x11316A70 / 0x11316A78 are two names `Show` takes.

Not done in the unit (7 functions): 0x108C05D0 (`StringC<256>::Data`, 4 bytes), 0x108C0650 (`mov eax, ecx`),
0x108C0660 / 0x108C06C0 / 0x108C07D0 (1-byte `ret`), 0x108C0730 (a second copy of the array's `Size()`),
0x108C0880 (`mov eax, [ecx]`): kept copies of classes the unit does not otherwise show; and 0x108C1280, the array's
destructor: the unit's manager destructor expands it inline, but giving `ArrayDynamic<T, AllocatorNew>` a destructor
changes every other user of that header (shader palette, geometry and polyskin loaders), so the kept copy stays
unreconstructed.

## engine/scenario/scenarioconditions.cpp (0x108C14A0 - 0x108C2770): 80 functions match, 0 nonmatching, 13 equivalent

The fight conditions of the scenario system (no assert path; file and member names are guesses, the class names come
from the RTTI and the property names from the reflection strings). The unit holds three whole classes
(`ScenarioGameObjectCondition`, `ScenarioScriptAttributeCondition`, `HasTagCondition`: constructor, destructor,
setters, property list, factories) and the `Evaluate` of five more whose constructors and properties are in the
unit at 0x108FF340 - 0x10900260 (`ScenarioMessageCondition`, `ScenarioStringCondition`, `ScenarioPropStateCondition`,
`ScenarioGameObjectAttributeCondition`, `ScenarioGameObjectTouchesTriggerCondition`), plus the getters of the last
two. `RegisterScenarioConditionFactories` (0x108C2570) registers all eight under their script names.
- The fourth argument of `Evaluate` is not used: the node the condition is asked about is the *third* (`c`), a
  `ScriptOwner` (`code/engine/scenario/scriptowner.h`, shared with luatracks.cpp, whose `ScriptOwnerPart` is the
  `ScenarioMessage` inside it: `GetPart` is `this + 0x10`, the message id is the word at +8). A kind of 1..0xFFFF means
  the node has its own message.
- `fight::PropertyEnumListObject<T>` (setter and a `fight::ListObject*`, 0x18 bytes) was added to trackfactory.h; the
  handle slots of the three classes are picked from `gAffiliateLister`.
- The enum of `ScenarioScriptAttributeCondition::SetType` is the table at 0x11316678 (11 entries, count at 0x10E74294)
  of another unit; the value member is an 8-byte typed value (`AttributeValue`, 0x108718B0 / 0x10872050 /
  0x108724B0 / 0x10872060 / 0x10871AF0, another unit); its `ToString` answers a pointer into one static buffer, so the
  engine's comparison of two such values (`ScenarioScriptAttributeCondition::Evaluate`) compares equal whenever both
  attributes exist.
- The three `ClearProperties` (0x108C1620 / 0x108C1690 / 0x108C16B0) had no row in functions.tsv; rows were added.
- An early `if (!ok) return false;` where `ok` is a local bool laid the false returns out like the engine's; the engine
  expands the game object table test of the handle a message carries (as `IsValid` does) but calls the out-of-line
  `IsValid` (0x1006B210) for the cached handle of `ScenarioGameObjectCondition`; ours either inlines both or calls
  both, which is why that function is EQUIVALENT with the other seven `Evaluate`s (they also differ in the engine's
  `add eax, -1` for `kind - 1`, which no expression of ours produced).
- Not done: 0x108C1570 / 0x108C1590 (`GetHandle(0)` / `GetHandle(1)` wrappers of an unknown class), the property
  setters and getters of the other five classes (the other unit).

## engine/audio/audioscriptmanager.cpp (0x108D1140 - 0x108D35E0): 87 functions match (the script method wrappers)

engine::AudioScriptManager (RTTI name of the wrappers; the class has no data): the scripts' access to the audio
system, registered as the snd_* functions of the script context by its constructor (0x108D2E90). The unit instantiates
`Method0..4/7/8` and `Closure0..4/7/8` (engine/function.h; Method7/8 and their closures were added, with the matching
`LuaScriptManager::RegisterMethod` overloads) for the signatures of the functions (all `void` except
`snd_GetListenerOffset`), the `RegisterMethod` templates and the kept copies of the wrappers' `Call` members. The
wrapper members are mapped by the class they belong to: where two classes have bodies identical to the byte
(`Method3<..., const char*, const char*, LuaGOH>` / `<..., const char*, unsigned int, unsigned int>`), the vftable of
the class (rtti.tsv) names the `Invoke`, and the `Call` next to it belongs to the same class.
- Not done: the functions themselves (0x108D1140 - 0x108D1720, 0x108D22C0), the constructor 0x108D2E90 and the
  allocation helpers (0x108D1310 - 0x108D1390, 0x108D2290, 0x108D35B0).

## engine/metafactories.cpp (0x108D6E20 - 0x108DE180): 332 functions match (class factories and their registrations)

The content library loads a reflected class through a `content::MetaObjectFactory<T, 1>` (LoadObject-derived
classes: slot 2 makes the object, `new T` through `LoadObject::operator new`) or a `content::MetaInstanceCreatorImpl<T,
1>` (plain classes: `new T`), registered from a function-local static of a per-class registration function (the
engine's start-up tables 0x108DE660 / 0x108DF1F0 / 0x108DFE50 expand those registrations in place). The unit holds, per
class, `content::GetClassMetaType<T>()` (76 bytes), the factory's constructor (37), `Create` (24/27) and the
registration (70): `code/content/metafactory.h`. 83 classes are done (39 factories, 15 creators and 29 behaviour
creators: `engine::MetaBehaviourCreatorImpl<T>`, whose slot 1 makes the behaviour with `new T(owner)` and whose slot 0 is
the library's generic creation, 0x10841FB0).
- The classes belong to other units: `engine/reflectedclasses.h` stands in for the ones not reconstructed yet (their
  size, constructor and the two reflection functions; replace an entry by the real class when its unit is done).
  `FmvSubtitleManager` is 0x18 bytes (one word past the array that the constructor never touches).
- Not done: the classes whose `Create` or reflection lies in another unit (the Attribute / ConstAttribute / extractor
  creators, 0x108D8B60 - 0x108D9130 and 0x108DA0A0 on; the camera, cinematographer, game object and prop classes with
  their own allocation), the nested classes of the content manager, the creators whose constructor is inline (messages,
  math::AABB / OBB / Plane / Sphere) and the three start-up tables.

## engine/online/onlinescripting.cpp (0x108C2B80 - 0x108C66A0): 35 functions match (script method wrappers)

The `Method` / `Closure` wrappers and `RegisterMethod` instances of three online classes whose units are not
reconstructed (engine::Replay, engine::ConsoleManager, engine::OLSStorage). The classes with several bases have
method pointers of two words (the closures carry a 0x28-byte function): `#pragma pointers_to_members` asks for that
on the forward declarations; ConsoleManager (one word) is instantiated before the pragma. Where two classes have
identical bodies (the `Method0<..., void>` constructors and `Call`s of Replay and OLSStorage) the vftable of the class
(rtti.tsv) names the `Invoke`, and the constructor's vftable immediate tells the constructors apart.

## pure3d animation and the choreo pose blending

Three units, none of them named by an assert except the first:

- `code/pure3d/anim/src/animation.cpp` (0x106E2A30 - 0x106E7BE0): the key readers of the channels (`ChannelKeys<T>`
  with the compressed rotations), `FrameTime`, `Animation::Touch`. Source in `pure3d/anim/src/animation.cpp`,
  `pure3d/channel.h`, `math/compressedquaternion.h`.
- `code/pure3d/anim/src/posedata.cpp` (0x10707240 - 0x10709AA0, asserts) and the pose controller around 0x10732100.
  Source in `pure3d/anim/src/{pose,posedata,poseanimationcontroller}.cpp`, `pure3d/{pose,posedata,posecontroller}.h`.
- `choreo` (RTTI: `choreo::Puppet`, `Driver` and its subclasses; asserts name `poseblendjob.cpp`,
  `deltatransform.cpp`): the puppet update, the pose blend job and the sampling of channels into poses. Source in
  `choreo/src/{puppet,poseblendjob,poseblend,samplechannels,drivers}.cpp`.

| Address | Function | Status |
|---|---|---|
| 0x106E2FE0 / 0x106E3010 / 0x106E3030 | FrameTime::FrameTime() / FrameTime(float) / SetFrame(short) | match |
| 0x106E3070 / 0x106E3080 / 0x106E30C0 | ChannelKeysBase::SetMode / Set, ChannelKeys<float>::Set (were SetFrames / Set with the wrong argument order) | match |
| 0x106E34E0 | ChannelKeysBase::FindKeys (binary search for the keys around a time) | EQUIVALENT (99 % of the instructions: the engine repeats a comparison the optimizer removes from our form) |
| 0x106E3A40 / 0x106E3A60 | GetKey<float> / GetKeys<float> | match |
| 0x106E3CC0 / 0x106E3CE0 / 0x106E3D60 / 0x106E3D80 | GetKey / GetKeys of the 16-bit and 8-bit compressed rotations | match |
| 0x106E3E10 / 0x106E3F50 | math::CompressedQuaternion6 / 8 ::ToQuaternion (COMDAT copies of inline members) | match |
| 0x106E41C0 / 0x106E6350 / 0x106E69B0 | ChannelKeys<float / CompressedQuaternion6 / CompressedQuaternion3>::Evaluate | match |
| 0x106E7B20 | Animation::Touch | match |
| 0x106DD6E0 / 0x107098A0 | Pose::Update / PoseData::Update | match |
| 0x10708E00 / 0x10708330 | PoseData::UpdateLocal / UpdateWorld (local matrices from rotation, scale, shear and pivots; joint and skinning matrices) | EQUIVALENT (SSE intrinsics: same operations, other schedule; UpdateLocal has the engine's size) |
| 0x10732320 | PoseAnimationController::Apply (animation channels over the pose with a weight, root motion as a delta) | EQUIVALENT (registers; the flow and the frame size are the engine's) |
| 0x10949080 | choreo::Puppet::Update (fades, drops finished drivers, steps the rest) | EQUIVALENT (x87 load of the step hoisted in the engine; a stack slot for the next entry) |
| 0x109560C0 | choreo::UpdateDriver (the driver type's update function) | match |
| 0x109580C0 / 0x109580E0 | PoseBlendCursors / PoseBlendBuffers constructors | match |
| 0x10958120 | PoseBlendBuffers::Fill | match |
| 0x10958210 / 0x10958D50 / 0x10959150 | HasLastNodes / ApplyRootNodes / UpdatePuppets | match |
| 0x10958DA0 | RunPoseBlendJob (the task body of a batch of puppets) | match |
| 0x10957690 / 0x10957710 / 0x10958640 / 0x109586E0 | the job's file-local report and delta-validation helpers (`static`, register arguments) | match |
| 0x109577A0 - 0x10957850, 0x109582E0 / 0x10958360 / 0x10958400 | PoseBlendSample: Set, the three root getters, BlendValue / BlendJoints / BlendMatrices | match |
| 0x10957870 - 0x10957A20 | PoseBlendNode setters (SetWeights, SetRootParts, SetNone, Set, SetJoint, SetPose, the mode and root rotation / translation setters, SetEmpty) | match |
| 0x10957F60 - 0x10958090 | PoseBlendRootTask / PoseBlendLimbTask setters and Apply, the two task ranges' Apply | match |
| 0x109581F0 / 0x10958200 / 0x10958220 | PoseBlendBuffers::HasRootNodes / HasRootTasks / the root range loop | match |
| 0x10958490 / 0x109585F0 | PoseBlendBuffers::Count (carves the blocks), PoseJointMask::Assign | match |
| 0x10958250 | PoseBlendBuffers limb range loop | NONMATCHING: defining it (with Count and the other loops) lets the compiler prove RunPoseBlendJob's buffers do not escape, so its last call becomes a tail call and RunPoseBlendJob drops to 92.9 %; the body is written under `#ifdef NONMATCHING` |
| 0x10958770 | PoseBlendSample::BlendRoot (root motion into the root matrix and the first scale) | EQUIVALENT (94 %: scale block multiplies and registers) |
| 0x10957A40 / 0x10957B20 / 0x10957E10 | PoseBlendNode::BlendRootJoint / BlendJoints / BlendPose | EQUIVALENT (98.6 % / 43.7 % / 72 %: register allocation and element pointers) |
| 0x10952150 - 0x109521A0 | SampleChannels::GetRotation / GetTranslation / GetUnknown10 / GetScale / GetUnknown14 / GetUnknown1C | match |
| 0x10953A90 / 0x10953160 | SlerpRotation / RotationBuffer::BlendInto (four-wide spherical interpolation of rotations) | EQUIVALENT (SSE intrinsics, other schedule) |
| 0x10953E40 | SampleChannels::Blend (channels sampled over joints first to last with a weight) | EQUIVALENT (stack slots; the engine's size) |

Matching notes:

- The compressed rotation keys are `short x, y, z` (six bytes) and `signed char x, y, z` (three bytes); w comes from
  the unit length. `ToQuaternion` is an inline member whose out-of-line copies exist; defined `inline` in the .cpp
  above its users, it is inlined into the one place where the engine inlines it and called elsewhere, and the
  annotation sits on the definition. `Max(1.0f - (...), 0.0f)` under the `sqrtf` and the four stores after the
  computation (a local `qw` first) give the engine's order.
- `ChannelKeysBase` is `{mode, count, frames}` and `ChannelKeys<T>` adds `values` (the old guess had frames and
  values in the wrong places; Float1Channel's fields follow). Evaluation clamps outside the keys and interpolates only
  when `mode` is set; the interpolated value is `((b - a) / (t1 - t0)) * (t - t0) + a`, tested as `alpha == 0.0f`
  first.
- `FrameTime(float)` is a constructor (it returns this), which is why `Float1Channel::GetValue` copies the temporary
  from the returned pointer.
- `Puppet::Update`'s comparisons `0.0f >= x` give the engine's `comiss 0, x` / `jae` forms (`x > 0.0f` gives the
  reversed operands); the loop is `for (entry = mEntries; index < count; entry++)` with `memmove(entry,
  &mEntries[index + 1], ...)`: indexing the next entry keeps a separate induction variable like the engine's.
- `PoseBlendBuffers::Fill` matched only with the cursor stores in the struct's order and the `counts` pointer
  declared after them, right before the loop (declaration order decides which of the buffers and the counts gets the
  callee-saved register).
- SSE intrinsics (`<emmintrin.h>`; `cvttps2dq` is SSE2): VS2005 passes the first `__m128` argument in xmm0 and
  refuses further `__m128` parameters by value (C2719), so four-vector helpers are macros or take references. A
  `static` function whose callers it can see gets the register convention for its pointers too; an `inline` function
  keeps cdecl pointers on the stack like the engine's. Constant tables of the original (masks, coefficients packed
  four to a vector and used by shuffling a lane across the vector, the unit axes) are `extern const __m128` data
  symbols at their addresses. Exactness of the intrinsics code was checked bit for bit against the original on
  random inputs (including parallel, opposite and out-of-order rotations, every flag combination of the pose data
  and masked / unmasked channel blending).
- The row-times-matrix helper is `(x * m0 + z * m2) + (w * m3 + y * m1)`; the rotation matrix of a quaternion comes
  out of `(z, x, y, w)` / `(y, z, x, w)` shuffles of `q` and `2q`, with `diagonal = (1 - yzx*2yzx) - 2zxy*zxy`.
- PoseData's flags: bit 0 local matrices out of date, bit 1 joint and skinning matrices out of date, bit 2 the
  further transform arrays (pivot, shear, a second offset) are in use. `mSpaces == 3` means all matrices exist.

## pure3d/src/context.cpp (0x1070ED50 - 0x10710930): 86 functions match, 2 EQUIVALENT

`pure3d::Context` (no RTTI: the class has no virtual functions) is the render context at `pure3d::context`
(0x1127F350, 0x7C bytes): a frame's times, the view, the passes' context and the wrapped drawable helper. `Startup`
(0x107107F0) makes it from a settings struct (the window handle at +0x10) and replaces the window procedure with the
unit's own `ContextWindowProc` (0x1070ED50, a WM_SIZE handler for `engine::gDisplay`); `Context::BeginFrame` /
`EndFrame` (0x1070EE70 / 0x1070EF00) open and close a frame on `pure3d::pddi`, the display and the passes' context.
The class derives from a `container::Map` (its first member is the tree; the node payload at +0x10 is destroyed by
0x106E2AA0 and the value at +0x20 is released through its vftable, the deleter is 0x107102B0).

Layout (read off the constructor): TreeBase +0; +0x1C the passes' context (vftable, slots 1 / 2 and 0x1074D880 with
the frame's render parameters), +0x20 the primitive stream, +0x24 unknown, +0x28 the view, +0x2C the drawable state,
+0x30 the maximum frame time 24000, +0x34 the frame number, +0x38 / +0x39 two flags (the second one is set while a
frame is built), +0x3C and +0x48 two `core::Time`s, +0x54 eight bytes, +0x5C a flag, +0x60 the helper (the context's
own one is embedded at +0x64), +0x68 the passes' chain, +0x6C a flag, +0x70 / +0x74 the pool of the frame's render
parameters (8-byte entries: a flag and the parameters at +4), +0x78 four unread bytes.

| Function | Status | Why |
|---|---|---|
| 0x107108A0 Shutdown | match | `delete context;` (the null check and the delete are one statement) |
| 0x107103E0 Context constructor | EQUIVALENT (64.2%) | same calls in the same order; the quad index loop keeps a zero-extended copy of its counter and the pool's empty-on-failure block sits elsewhere |
| 0x1070F380 DrawDebugText | EQUIVALENT (93.1%) | the loads of the font and of 0.5 are scheduled differently around the two stores of it |
| 0x1070FC90 LoadDebugFont | match (fragile: two locals trade stack slots when the included headers declare other names; VC8's slot order depends on the unit's symbol table) | registers the texture and font loaders when missing, loads the embedded P3D (0x10E58E38, 0x21F0 bytes) from a memory stream and takes "pure3d_debug_font" out of its inventory; the request is a `StringC<256>` followed by its words |
| 0x1070F5C0 / 0x1070F600 / 0x1070F650 AllocRenderParams / FreeRenderParams / UpdateRenderParams | match | the pool is a `ContextArray<FrameEntry>` (signed `Size()`), the loops index it with an unsigned counter |

The constructor and the destructor are written (the destructor matches; the constructor is EQUIVALENT). The subsystems
they start and stop are declared as `Unknown<address>` in `context.h`; the context's object of the display
(`gPddiDx`, 0x1127F358), the settings struct (`ContextSettings`, with its constructor 0x10710120) and the render
target parameters (`TargetParams`, 0x1074E5A0 / 0x1074E590) are named from their use. Findings:
- `Context::Context` keeps the pool of `RenderParams` (an `Entity`: 0x330 bytes, made with `RefCounted::operator new`)
  in a `ContextArray<FrameEntry>`; `FillCopies` (the fill with a constant value) must be `inline` for the constructor
  to expand it with zero stores while the out-of-line `Allocate(count, value)` calls it.
- The scoped locals of an inlined helper share their stack slots (`FindConstant` in `Unknown1070F850`); locals of
  one scope do not.
- The assert macro's last argument is the constant 0; the engine passes the register that is known to hold 0.

### The fourth session (2026-10-15, ds-7): the helper's slot 1 and what the rest of the unit is

- **0x1070FC60 is `WrappedDrawableHelper` vftable slot 1 and it matches** (100 %, `?Unknown1@WrappedDrawableHelper
  @pure3d@@UAEXPAVLoadInventory@content@@ABV?$Name@UCaseSensitiveKey@core@@@core@@@Z`). It builds a
  `content::LoadInventory::DynamicCaster<pure3d::Drawable>` and calls the inventory's slot 5
  (`FindObject(&caster, name, true)`), dropping the answer. That fixes the defect the third session left: our
  vftable's slot 1 was an empty stub, so in the hybrid DLL the context's own helper did nothing. `vtcheck.py`
  (333 vftables, 0 problems) and `vtcheck.py --all` are clean for `??_7WrappedDrawableHelper`.
- Two symbols were mapped for it: `?Unknown1@WrappedDrawableHelper@pure3d@@...` = 0x1070FC60 and
  `??_7?$DynamicCaster@VDrawable@pure3d@@@LoadInventory@content@@6B@` = 0x10E5B1CC (the engine's slot 0 at that
  vftable is 0x1070F7D0, which is `DynamicCaster<Drawable>::Cast` - a kept copy in this unit).

**The unit's shape, read off the constructor 0x107103E0 and the neighbours.** Besides the `Context` and its
`WrappedDrawableHelper` (0x1070ED50 - 0x1070EF00), the object carries a whole block of template instantiations, so
most of the addresses in 0x1070F1E0 - 0x1070FBE0 and 0x1070FF50 - 0x10710370 are the engine's container members, not
hand-written functions:

- `container::TreeBase::Node`'s payload at +0x10 is a `Pair` of a 0x10-byte **key** and a 4-byte **value**; the
  value is the frame's `RenderContext*` (0x1070FFA0 calls its slots 0 / 1 / 2 and 0x1074D880 on it, 0x10710190 and
  0x10710370 release / AddRef it). Node size 0x28 (`operator new[](0x28)` in 0x10710230), key at +0x10, value at
  +0x20. The key starts with a `core::Name` (`GetHash` = 0x1007EE20 is called on key+0x10 and the tree's own linear
  walk 0x1070FF50 compares the two 4-byte halves of that hash) and then holds a `const char*` at +8 with an "owns
  the text" flag at +0xC (0x1070F730 copies it - through `Name(const unsigned __int64&)`, i.e. the copy is written
  `name(other.name)` - and 0x1070FC20 / 0x106E2AA0 free it through `core::Free`).
- The map's own members: `Find` 0x10710090, `Erase(Iterator)` 0x10710040, `Insert` 0x10710230, `Begin` 0x1070FA60,
  `End` 0x1070FA80, the key comparator 0x1070FAB0 (`if (key < nodeKey) return -1; return nodeKey < key;` - note the
  `neg/sbb/neg` on the second test, ours in `container/map.h` writes `if (b < a) return 1; return 0;` and will not
  match), the node comparator 0x1070FB60, `MapNode(const Pair&)` 0x107100E0, `Pair(const Pair&)` 0x1070FBA0,
  `MapNode(const Key&, const Value&)` 0x1070FB40, the iterators (0x1070F690 / 0x1070F2B0 `operator->` = `pair` at
  +0x10, 0x1070F2C0 / 0x1070F6A0 `operator++`, 0x1070F270 / 0x1070F290 `==` / `!=`, 0x1070FA80 / 0x1070F230 a null
  iterator) and `Context::ClearEntries` (0x107103D0, done) / `DeleteContextEntry` (0x107102B0) on top of them.
- The frame pool at +0x70 / +0x74 is a **dynamic array of 8-byte entries** built with `operator new[]` and
  `operator delete[]` (0x107DEF70 / 0x107DEFE0): 0x1070F2E0 `Allocate(count)`, 0x1070FAE0 `Allocate(count, value)`
  (fills through 0x1070F790), 0x1070FAA0 the destructor, 0x1070F250 `Size()` (`sar eax, 3`), 0x1070F260
  `operator[]`, 0x1070F360 `Construct` and 0x1070F330 / 0x1070F350 the rest of one instantiation. The constructor
  inlines all of them, so the pool is *not* the raw byte pair the class header guesses - it is an
  `ArrayDynamic<T, Allocator>` whose allocator's `Alloc` takes one argument (ours in `container/arraydynamic.h`
  calls `Allocator().Alloc(size, 16)`), and `Context::RenderParamsCount()` is its `Size()`.
- **The unit is smaller than the address range suggests.** 0x1070E790 - 0x1070ED40 (the "add_color" /
  "distortion_shape" code, `GetClientRect` / `GetWindowRect` on `Context::sWindow`, a 0x4E0-byte object built at
  0x1070EA40) is a **neighbouring unit**, not `context.cpp` - it works on a different object (+0x3B0, +0x474,
  +0x4D4) and its asserts would name that file. 0x1070ECE0 / 0x1070ED00 (the `surface->info[i].size->width`
  accessors) and 0x1070ED20 / 0x1070ED30 / 0x1070ED40 belong to it too. `context.cpp` starts at 0x1070ED50.
- The unit's other debug-draw members: 0x1070F380 draws a line of text (a `RenderStateBackup`, then the font at
  Context+0x24 through slots 0x14 / 0x18 / 0x44 / 0x2C) with the two globals at 0x11281398 / 0x1128139C as the
  scale; 0x1070F540 is its "y + the font's height" wrapper; 0x1070EF80 renders the colour / depth `RenderTarget`s
  (protopass.h) through `0x1074E5A0` and runs the passes; 0x1070F850 sets `p3dTimeElapsed` / `p3dTimeCos`; 0x1070FC90
  loads `dummy.p3d` and keeps the `pure3d_debug_font` `TextureFont` at Context+0x24; 0x10710120 builds a 0x4E0-byte
  object (10000, the 0x10E5DA34 default, `FUN_106179B0` / `FUN_10714D60`, +0x16C = 8) which is the `RenderParams`
  the pool holds.
- 0x1070EDB0 / 0x1070EDD0 are the scalar deleting destructors of two classes whose destructors are another unit's
  0x1074D730 and 0x1061BEC0; 0x1070F680 / 0x1070F6E0 / 0x1070F780 / 0x1070F7C0 / 0x1070F7F0 / 0x1070F820 /
  0x1070F840 are `TreeBase` and `DynamicCaster` members, and 0x1070F7D0 / 0x1070F800 are the `Cast`s of
  `DynamicCaster<Drawable>` (0x10E5B1CC) and `DynamicCaster<pure3d::TextureFont>` (0x10E5B1D4).

Still not done after this session: everything above except 0x1070FC60. The tree / pool members cannot be claimed
with a `// FUNCTION:` annotation while they live in `container/map.h` and `container/arraydynamic.h` (configure.py
only scans `src/**/*.cpp`), so matching them means giving this unit its own copy of the two containers - with the
one-argument allocator and the `return b < a;` comparator - and then writing the `Context` members on top of it.
0x1070ED20 / 0x1070ED30 (empty, one byte of `ret`) are the only trivial ones left in the neighbouring unit.

### The container instances (sn-render)

The tree and the pool are written in `code/pure3d/context.h` as `ContextTree<Key, Value>` (the shape of `container::Map`)
and `ContextArray<T>` (begin / end over `operator new[]`; `operator delete[]` called directly) and their members are
claimed with explicit instantiations at the end of `context.cpp`. Findings:
- The tree's key (0x10 bytes) is a 64-bit name (`ContextName`: its constructor / `GetHash` are the engine's
  `core::Name<CaseSensitiveKey>` copies 0x1007EE00 / 0x1007EE20, mapped, not defined here, so the compiler cannot
  see which registers they keep), a `const char*` and the owns-the-text flag. The 64-bit word makes the key 8-byte
  aligned: nodes are 0x28 bytes and the `Pair` a function keeps on its stack is 0x18 (a `__declspec(align)` would
  realign the stack; a natural `unsigned __int64` member does not).
- `Compare` is `if (a < b) return -1; if (b < a) return 1; return 0;` (the engine's `neg / sbb / neg` is how `if (x)
  return 1; return 0;` compiles).
- The scalar deleting destructors 0x1070F820 / 0x1070FC30 appear when the destructors of `ContextKey` / `MapNode` are
  explicitly instantiated; 0x1070EDB0 / 0x1070EDD0 / 0x10710880 are written as `DeleteThis(flags)` members.
- `RunContext` (0x1070FFA0): the two stores of the picture size come after the virtual call's table load only when
  they go through a pointer and two named floats.
- `ContextSettings` has a constructor (0x10710120): 10000, a constant of the image (0x10E5DA34), true, 2, then the
  two sub-objects' constructors, -1, 8 drawables.

Findings carried over from the third session:

- The unit is `context.cpp`: 0x1070EF80 (line 790), 0x107107F0 (line 92) and 0x107108A0 (line 119) carry the path.
- `ContextWindowProc` is a `__stdcall` free function (the mangled name is in symbols.txt); the engine's imports are
  called through their `__imp__` slots (`GetWindowLongA` / `SetWindowLongA` / `CallWindowProcA`).
- The constructor shows the class's size (0x7C), the settings layout and that the embedded helper's vftable is
  stored inline (so `WrappedDrawableHelper`'s constructor is defined in its class body, and 0x1070EDA0 is a kept
  copy). The helper's vftable 0x10E5B114 has two slots: 0x1070ED90 (returns its argument) is slot 0 and 0x1070FC60
  is slot 1 (found and matched by the fourth session, see above).
- `Context::Startup` reads the window from the settings *through the static* it just wrote
  (`sWindow = settings.window; sPreviousWindowProc = GetWindowLongA(sWindow, -4);`) - that is what makes the
  compiler reuse the register instead of reloading the settings.

## choreo/src/rootdriver.cpp (0x1094EF30 - 0x1094F805): 32 functions match, 5 NONMATCHING, 0 not done

The unit after deltatransform.cpp. It holds `choreo::RootDriver : Driver` (RTTI 0x111EC1A0, vftable 0x10E8C1D4,
constructor 0x1094EF30, driver type 9) and `choreo::AnimationDriver : PartitionDriver` (RTTI 0x111EC240, vftable
0x10E8C2F4), plus the helpers around them.

`choreo::Driver` (the base of every driver) has five vtable slots: 0x109496E0 (slot 0, `ret 4`, the bind hook),
0x109496F0 (slot 1, `ret`, the release hook), the two pure virtuals of slots 2 and 3 (`__purecall` in the base's
vftable, every driver class overrides them), and the destructor in slot 4. Its constructor is 0x1094A4E0:
`{ vptr, core::Name +4 (an 8-byte name built by 0x1005E520), unknown +0xC, int +0x10 = 0, type +0x14,
flags byte +0x18 }`, 0x1C bytes; the flag bits are set by 0x1094A440 (bit 1, takes part in the blend), 0x1094A4A0
(bit 4, moves the root) and 0x1094A4C0 (bit 5, the owner stopped the driver).

`choreo::PartitionDriver` (0x38 bytes) adds the joint range it drives: `mFirstJoint +0x20`, `mLastJoint +0x24`
(the overrides of slots 2 and 3, 0x1094B100 / 0x1094B110), `mPose +0x28` (the object of the DriverInfo it was bound
with), `mJoint +0x2C` (whose name is at +8 and whose joint mask is at +0x10), `mJointMask +0x30`, and slot 5
(0x1094D4B0) `mFirstJoint == 0` (`CoversRoot`).

`choreo::AnimationDriver` (0xF0 bytes): `AnimationBinding mBinding +0x38` = `{ pure3d::Animation* mSource +0,
AnimationClip mClip +4 }` (the binding's destructor is 0x10955560: release the animation, destroy the clip)
`| +0x54 mUnknown54 (the driver moves the root translation) | +0x55 mUnknown55 (the rotation) | +0x58 rate |
+0x5C first frame | +0x60 last frame | +0x64..+0x67 the four root motion flags | +0x68 DeltaTransform |
+0xE4 the current frame | +0xE8 a direction | +0xEC the frame the step started at`. The clip is
`{ channel +0, duration +4, rate +8, +0xC, flags byte +0x10, the animation bound to it +0x14 }` (methods
0x10952290 - 0x10952480 and the samplers 0x10955260 / 0x109552C0 / 0x10955360, all in the sample channel unit).

Match (new): the RootDriver constructor 0x1094EF30 and destructor 0x1094EF80, BlendIntoMatrix's neighbours
0x1094F040 FillPose (the pose blend node's `SetNone` / `SetRotation` / `SetTranslation`), the AnimationDriver
destructor 0x1094F200, SetAnimation 0x1094F240, the Bind override 0x1094F290, the Unbind override 0x1094F2D0,
IsSet 0x1094F2E0, UpdateRest 0x1094F2F0, GetRangeTime 0x1094F3A0, 0x1094F420, GetTimeLeft 0x1094F440, the two
root motion flag setters 0x1094F4F0 / 0x1094F510, the CoversRoot override 0x1094F530, the two clip samplers
0x1094F630 / 0x1094F670 and the blend node filler 0x1094F6D0. Both classes' vftables are emitted by this object
(the type-9 casts 0x1094EFA0 / 0x1094EFC0, GetFirstJoint / GetLastJoint 0x1094EFE0 / 0x1094EFF0, SetMask
0x1094F000, RootDriver::Update 0x1094F020, the four flag getters, the type-0 cast 0x1094F230, ClampFrame
0x1094F5C0, GetFrameAdvance 0x1094F5F0 and SetUnknownE4 0x1094F610 were already matched).

Matching notes:

- The two float locals of GetRangeTime and GetTimeLeft (`float to = ...; float from = ...; float rate =
  mClip.GetFrameRate();`) are what keeps the engine's two operand spills: without them the compiler folds the
  members into the members and subtracts before the call.
- `mDelta.Transform::Reset()` (a qualified call) is the engine's call to 0x1094D910, a thunk of `Transform::Reset`;
  `mDelta.Reset()` would be the DeltaTransform overload at 0x1094D920.
- The vftable of a class with a virtual destructor holds the *vector* deleting destructor (`??_E`), the engine's
  holds the scalar one (`??_G`); both of ours are byte-identical to the engine's function, so `??_E` is mapped to
  the same address in symbols.txt.

NONMATCHING:

- 0x1094F300 SetStartFrame, 0x1094F350 SetEndFrame: every instruction is the same but the engine encodes the two
  float comparisons with `comiss` of the constant and then of the frame against the limit, ours always puts the
  argument first (`comiss frame, value`); 90 %. No spelling of the condition changes it.
- 0x1094F0A0 BlendIntoMatrix: the engine keeps the copy of the matrix translation in the lower of the two
  `math::Vector` locals (the one the delta transform's position is returned into in ours); every instruction after
  that follows from the two slots; 36 %.
- 0x1094F550 ClampFrame: the engine keeps the comparisons of the frame's ends as they are written (the minimum on
  the left) where ours are canonicalised into the other order, the same two bytes twice; 74 %.
- 0x1094F6B0: the engine loads both frames before the call and pushes their slots one at a time, ours loads the
  second frame first into an argument area of its own; 35 %.

## choreo/src/deltatransform.cpp (0x1094D730 - 0x1094EF30): 25 functions match, 10 NONMATCHING, 1 not done

`choreo::DeltaTransform` (the asserts at 0x1094D730 - 0x1094ECC0 name the file and the class): the movement of a
character over one step. It derives from a `choreo::Transform` (declared in the unit before this one, not
reconstructed: a `math::Matrix` at +0, the `math::Quaternion` it was decomposed to at +0x40, the three axis scales at
+0x50 - +0x58 and the mode at +0x5C saying which of the two is current) and adds the linear delta at +0x60, the
angular delta at +0x6C and the two "was set this step" flags at +0x78 / +0x79 (size 0x7C). The unit is told either the
two deltas or the root matrix the step ends on and gives back the matrix, the position, the rotation or the facing
vector.

The unit is one `// FUNCTION:` block per function in address order; the four overloads of the file-local
`ValidateDeltaInput` and the two reports the asserts call are the validation layer. Matching notes:

- The reports are `core::Report(0, "Choreo  Pre ", FILE, line, 0, format, ...)` behind a per-site `static bool`, and
  the assert sites are the `OLD_ASSERT_AT(FILE, line, ValidateDeltaInput(x), "ValidateDeltaInput( x )", "")` macro
  (the expression text is the engine's, the developer message is `""`).
- `math::Vector` copies from a reference are component-wise, not a block copy: `mVelocity.Set(0, 0, 0)` in the
  constructor and three separate assignments in the delta setters give the engine's `fld` / `fstp`; `mVelocity = v`
  gives integer `mov`s.
- The reports and the four validators are file-local (`static`), as the engine's are: VS2005 gives a function with
  internal linkage its own register convention (here the argument in `eax` or `esi`), so declared `static` they and
  every setter that calls them match; with external linkage they take their argument on the stack and every caller
  is one `mov` off.
- The order the two zero vectors are written in decides the constructor's match (`Set` forward) and the Reset's
  (the engine writes each vector's components backwards; 88 % is the best reached).

NONMATCHING:

- 0x1094DB40 ValidateDeltaInput(float): the engine takes the float through a pointer in `eax` (a `const float&`
  parameter is the next thing to try); 26 %.
- 0x1094D920 Reset: 88 %, the component order of the two zero vectors.
- The setters that call the float validation or rebuild a matrix: 0x1094DC90 / 0x1094DE80 (SetVelocity /
  SetAngularVelocity with a matrix, 43 %), 0x1094E3C0 SetDelta(float) (46 %), 0x1094E490 / 0x1094E5A0 SetOrientation
  with an angle (41 % / 43 %).
- 0x1094ED90 Update: 25 %, the engine expands the identity matrix into sixteen locals and schedules the two branches
  differently.

Not done (1): `ValidateDeltaInput(const math::Matrix&)` (0x1094DA40) is compiled and called by the matching matrix
setters but carries no annotation (the engine unrolls its sixteen comparisons where ours keeps the loop).

## choreo/src/partitiondriver.cpp (0x1094C790 - 0x1094D6F0): 50 functions match, 0 NONMATCHING, 0 not done

The unit before deltatransform.cpp (file name guessed): `choreo::AnimationBlendDriver : PartitionDriver` (RTTI
0x111EC030, vftable 0x10E8BB64, driver type 1) and the partition half of `choreo::PartitionDriver` (RTTI 0x111EBF84,
vftable 0x10E8BC84). Classes in `choreo/blenddriver.h` and `choreo/rootdriver.h`.

- `PartitionDriver` (0x38 bytes): the object at +0x28 is a `pure3d::Skeleton` (not a Pose: its +8 is the joint count
  and its virtuals 0 / 1 are AddRef / Release), `mPartition +0x2C` is the skeleton's named group of joints
  (`pure3d::SkeletonPartition`, 0x18 bytes, name at +8, joint mask at +0x10; the skeleton keeps the count at +0x58 and
  the array at +0x5C, `Skeleton::FindPartition` 0x106DDC80), `mJointMask +0x30` its mask (a bit per joint). The ranges
  `mFirstJoint` / `mLastJoint` are the first and last set bit (0x1094D570); `SetPartition` ends with a virtual call
  of `CoversRoot` whose result is dropped.
- `AnimationBlendDriver` (0x2E4 bytes): `mActiveCount +0x38`, fifteen `BlendEntry` (0x2C bytes: `AnimationBinding` +0,
  start frame +0x1C, end frame +0x20 (negative counts back from the last frame, default -1), rate +0x24, weight +0x28)
  from +0x3C, `mLooping +0x2D0`, +0x2D1, `mScale +0x2D4`, `mPreviousPhase +0x2D8`, `mPhase +0x2DC`, `mPhaseStep +0x2E0`.
  The entries are blended by weight (a running mean, `(x - mean) * share + mean`) into one phase running from 0 to 1.
- `PoseBlendSample` is 0x20 bytes: the joint arrays that `PoseBlendNode::Set` takes start right after the samples,
  not in a member.

Matching notes:

- The file-local register convention blocker recorded earlier does not exist: every helper of this unit takes its
  arguments on the stack or in `ecx`. The `RefAssign` pair at 0x1094D1C0 / 0x1094D4F0 are `core::RefAssign` for
  `pure3d::Animation` and `pure3d::Skeleton` (instantiated by the compiler, not annotated).
- A `bool` function returning `return !(a && b);` is compiled with `xor eax, eax` / `mov eax, 1`, `if (...) return false;
  return true;` with `xor al, al` (BlendEntry::IsIdle).
- The engine's clamp ladders are ternaries: `float s = x >= 0 ? x : 0; if (s - last >= 0) s = last;` keeps the
  intermediate in a register, a plain `if (x < 0) x = 0;` stores it in the stack slot (GetLength / GetFrame; the
  wrapped end frame is a separate local).
- A reciprocal guarded by an epsilon is `if (EPS >= fabsf(x)) r = 0; else r = 1 / x;` (zero branch first, `fcomip` against
  the constant) or the ternary `!(EPS >= fabsf(x)) ? a / x : 0`; `fabsf(x) > EPS` compiles to `fxch` + `fcomip` instead.
- A float result assigned in each arm of an if / else chain and returned (`float result; ...; return result;`) is
  spilled to a stack slot and reloaded (`fstp` / `fld`) like the engine's GetFrame.
- `UpdateFinished`: `finished = mPhase >= 1.0f` in the `mScale >= 0` arm and `0.0f >= mPhase` in the other share one
  flag test; any `playing` variable breaks that.
- `SetAnimation`: `movesRoot = movesRoot || clip.Unknown10952380();` (not `if (...) movesRoot = true`) keeps the engine's
  register split of `this`.

## pure3d render module (src/drawable.cpp, src/scene.cpp, visibility/src/server.cpp and neighbours)

The render object of an engine drawable is a `pure3d::Drawable` (RTTI name, vftable 0x10E55238; the engine side
used to call it DrawableImpl, which is now a typedef in `drawableimpl.h`). Its unit runs 0x106DE950 - 0x106E28F0;
`pure3d::Scene` (vftable 0x10E5B358, the engine's "render list") 0x10710930 - 0x10714400; the visibility server
0x10726540 - 0x10729AE0. Paths below `code/pure3d/` are guessed from the class names.

| Address | Function | Status |
|---|---|---|
| 0x106DEA40 / 0x106DEBE0 / 0x101E0520 / 0x10444290 / 0x10433D90 | core::BitField Test / Set(bit, value) / Set / Clear / ClearAll (COMDAT copies) | match |
| 0x106DF480 | pure3d::GetCurrentFrame | match |
| 0x106DF4F0 / 0x106DF520 / 0x106DF620 | Drawable::IsPoseCurrent / IsCyclic / GetPose | match |
| 0x106DFFD0 | Drawable::Update(dt) | EQUIVALENT (72 %: loop registers) |
| 0x106E0680 | Drawable::MarkPoseDirty | match |
| 0x106E0D60 | Drawable::UpdateBounds(force) | EQUIVALENT (39 %: registers, frame 4 bytes larger) |
| 0x106E13C0 | DrawablePart::GetWorldMatrix | match |
| 0x106E14E0 / 0x106E18A0 | Drawable::UpdatePart / UpdateParts | match |
| 0x10710B40 / 0x10711400 | Scene::GetUnknownD8 / UpdateDrawables (the AsyncDrawableUpdate task body) | match |
| 0x107283A0 | visibility::RunTest (the frustum test task body) | EQUIVALENT (index and constant registers) |
| 0x102CBD60 | math::AABB::Inflate (COMDAT copy, defined in drawable.cpp) | match |
| 0x106F31D0 / 0x106F3630 / 0x106F4100 | RenderStateBackup::Restore, PrimStream::End / Begin (src/primitive.cpp) | match |
| 0x10707680 / 0x10707B00 | MeshState::GetController3, ShaderParameters::operator= (src/mesh.cpp) | match |
| 0x10709CE0 | ParticleSystemState::GetUnknown490 (effects/src/particlesystem.cpp) | match |
| 0x106ED9D0 / 0x106EDA80 / 0x106EDC90 / 0x106EDCA0 | ParticleSystemState::GetUnknown4BC, GetParticleManager, ParticleManager accessors (effects/src/particlemanager.cpp) | match |
| 0x102CD6D0 | math::pddiColour(const Vector4&) (COMDAT copy, defined in particlemanager.cpp) | EQUIVALENT (clamp test order) |
| 0x1070EE10 | Context::GetView (src/context.cpp) | match |
| 0x1071B200 / 0x1071B210 | SkinState::GetExpression / GetExpressionState (atg4/platform/win32/skin.cpp) | match |
| 0x10731700 | VertexOffsetExpressionMixer::Apply | match |
| 0x106E3070 / 0x106E3080 / 0x106E30C0 | ChannelKeysBase::SetFrames / Set, ChannelKeys<float>::Set (anim/src/animation.cpp) | match |
| 0x107350B0 | Float1Channel::GetValue (src/channel.cpp) | match |
| 0x1074F3B0 / 0x1074F3C0 | RenderParams::GetViewState / GetCameraData | match |
| 0x10756AA0 | LightingScene::GetLights (lighting/lightingscene.cpp) | EQUIVALENT (the engine's loop is unrolled 4x) |
| 0x1075C750 | MergeLightBits (lighting/src/light.cpp) | match |
| 0x107A6B10 | LightingInputs::SetShaderConstant | match |
| 0x1077FFD0 | Occluder::GetShadowPlanes (src/occluder.cpp) | EQUIVALENT (scheduling, 12 %) |
| 0x10860E80 | engine::render::RenderQueue::SendAndWait (engine/render/renderthread.cpp) | match |
| 0x10B7EF00 | (core event wait in the job queue area) | not done: left to the job queue unit |

Matching notes:

- `core::BitField<T>` members are defined outside the class (not inlined under /Ob1, COMDAT copies everywhere); the
  annotations sit on explicit instantiations in drawable.cpp. Set / Clear build the mask in a `T` local
  (`T mask = 1; mask <<= bit;`), which is what loads the bit with `mov cx, word ptr`.
- Flags read in place (`shr; test cl, 1`) come from inline accessors (`IsSet`, Primitive's `GetFlagN` over
  bit-fields); a mask OR through an inline member (`SetMask`) keeps the original's store order around it, a direct
  `mBits |= 4` is sunk below neighbouring stores.
- Bool functions written as `return !a || b;` return through eax (`xor eax, eax` / `mov eax, 1`), an if/return form
  through al.
- The part flag updates are `flags = value ? flags | mask : flags & ~mask` (an inline helper): the byte is loaded
  before the branch.
- `DrawablePart::GetBindingSource` (0x102D3D30 elsewhere) is inlined twice in UpdatePart; the state's half of it
  is itself an inline (it reloads the state's word), see `PrimitiveState::GetBindingSource`.
- Update's emitter matrix copy is a pointer loop counted `do ... while (--row >= 0)` (x87 copies, `jns`); the
  implicit copy of any matrix or row struct comes out as 16 unrolled movss.
- A self-recursive accessor (`return inherit ? parent->Get() : flag;`) becomes the engine's tail jump to its own
  entry; the if / return form and explicit loops are rotated into a do-while.
- Bit ranges as `x << 5` match where `x * 32` changes the load order.
- A global pointer read twice around a store through it is cached in a local in the source (`pddi`), and a nested
  member pointer as well (`Constants* constants = context->constants`) when the index global is loaded between.
- Member-wise copies of a struct with a bit-field and a Name member (ShaderParameters) are the compiler's implicit
  operator= of the element; the outer copy is written out (16-element loop) so it can carry the annotation.

## pure3d/texture (texture/src, unit 0x10729AE0 - 0x1072B7F0), 18 match, 3 EQUIVALENT

The texture module (`code/pure3d/texture/src/`; docs/original_tree.md has `bmp.cpp` there, this unit's file name is
a guess from it). One unit holds `pure3d::Texture`, the DDS helpers, `pure3d::TextureLoader` and the file parsers
`pure3d::TextureParser` / `pure3d::DDSParser`; the visibility server's unit ends exactly at 0x10729AE0.

The unit was compiled with `/arch:SSE2` (`// CFLAGS: /arch:SSE2` on the first line of `texture.cpp`, see
docs/toolchain.md): under `/arch:SSE` the calling conventions the compiler gives the file-local helpers differ from the
engine's. The helpers are `static`; the order the parameters are declared in decides which of them travel in
registers.

| Address | Function | Status |
|---|---|---|
| 0x10729AE0 / 0x1072A0E0 / 0x10729B00 | Texture constructor / destructor / Create | match |
| 0x1072A470 | TextureLoader::LoadObject (slot 7) | match |
| 0x1072A530 / 0x1072A540 / 0x1072A850 | IsBlockFormat, GetFormat, FillPixelFormat (static) | match |
| 0x1072AB40 / 0x1072ACA0 / 0x1072AD80 | ReadHeader, WriteHeader, RoundToBlock (static) | match |
| 0x1072AF20 / 0x1072AF80 / 0x1072B110 | SkipLevel, SaveLevel, SaveLevels (static) | match |
| 0x1072B050 / 0x1072B150 | UploadLevels, UploadCubeLevels (static) | match (once `UploadLevel` takes its parameters as stream, texture, rect, level, slice) |
| 0x1072B1F0 / 0x1072B300 / 0x1072B360 | SaveCubeLevels, SaveVolumeLevels, SaveTexture | match |
| 0x1072B420 | DDSParser::IsSupportedFormat (slot 1) | match |
| 0x1072B600 / 0x1072B6D0 | MakeTexture (static), DDSParser::Parse (slot 3) | match |
| 0x1072ADB0 | UploadLevel (static) | match |
| 0x1072B230 | UploadVolumeLevels (static) | matches |
| 0x1072B470 | DDSParser::Load (slot 2) | EQUIVALENT (22.6 %; same block layout as the engine's) |

The EQUIVALENT functions differ only in register homes and scheduling: UploadLevel keeps the rect in ebx where the
engine uses esi, tests `rect->x & 3` through a byte test, multiplies in the other operand order and orders two
additions differently; UploadVolumeLevels passes the texture on the stack where the engine passes it in edi (no
order of the parameters, local copy or loop shape made the compiler hand it over in a register, as it does for the rect
of UploadLevels); Load keeps the stream in a stack slot where the engine keeps it in ebx. SkipLevel reads the format
through a volatile access because the engine reloads it after the call.

`TextureLoader::LoadObject` (0x1072A470) matches once the loader bases exist: it is slot 7 of `content::SimpleChunkHandler`
(8 slots, RTTI), which is what the loader vftables 0x10E5C1D8 and the others hold. The bases are reconstructed in
`code/content/chunkhandler.h`: `content::ObjectLoader` (6 slots: LoadObject's five plus a pure `CreateObject`) and
`content::SimpleChunkHandler` (slot 5 `CreateObject` 0x1060B780, slot 6 the chunk flags at +8 0x105FFA40, slot 7 the
pure `LoadObject`). The reader the handler hands on is `content::ChunkReader` (0x288 bytes, stream at +0x284;
0x1060BB60 constructor, 0x1060B8E0 opens a chunk, 0x1060B8A0 asks whether one is left). `TextureLoader`'s signature is
`LoadObject(core::IRefCount** object, ObjectName* name, ChunkReader* reader, int flags)` - the object output is an
`IRefCount**` because a texture is a `pure3d::Entity`, not a `LoadObject`. Its workhorse 0x1072A1E0 takes
`(ChunkReader*, bool flag, int unknown)` and returns the `Texture*`. The class declares its destructor first and does
not define it, so the vftable stays with the engine's copy of the unit.

Renames this unit made: `pure3d::TextureUploader` (a guess of the render units) is `pure3d::DDSParser` — the
constructor 0x1072B3D0 installs 0x10E5C2C8, which rtti.tsv names `.?AVDDSParser@pure3d@@`. engine/render/async/
private/drawable.cpp's DoLoadTexture (0x107EAC90) was updated and still matches.

Matching notes:

- `pure3d::Texture`'s own vftable exists although the class declares no new virtual: it overrides the destructor
  (`virtual ~Texture();`), and an empty body still emits the `mov [ecx], ??_7Texture` store the engine's has.
- `Texture` keeps its `pure3d::dxTexture` (the back end's texture) at +0x10 and releases it through `ReleaseRef` in the
  destructor; `Texture::Create` (0x10729B00) makes it from a `TextureDescription` and an optional source texture.
- An empty 4-argument switch over a 24-value range (5 - 0x1C) comes out as the engine's byte index table feeding a
  two-entry jump table; the 8 table bytes after the code are part of the compared function.

- (op-finish) 0x1072ADB0 `UploadLevel` stays EQUIVALENT (84.7 %, was 46.6): the engine's `test dword ptr [rect + 8], 3`
  is the constant-first comparison `0 != (rect->x & 3)` (only two such tests exist in the image; `x & 3` in any other
  spelling gives `test byte ptr`). The rect in esi and the bits per pixel in ebx are swapped in ours. difftest SAME.
- (mp-load) 0x1072ADB0 `UploadLevel` stays EQUIVALENT, now 98.1 % (was 84.7): the row bytes are computed before the x offset
  in the rect block (`rowBytes`, `xBytes`, `y`), which gives the engine's rect in esi / bits in ebx, and the four block
  adjustments in the order row bytes, y, height, x give its interleaving. What is left is the operand order of two
  commutative operations, `lea esi, [eax + edx]` (offset + x bytes) and `mov ecx, pitch; imul ecx, y` (pitch times the
  skipped rows): no source order, declaration order, field type, loop form of the skip (it is strength-reduced to
  the product) or declaration position of the locals changes either. difftest SAME.
- (op-map1) 0x1072ADB0 `UploadLevel` **matches**: the lock description is cleared through a pointer (an inline
  `ClearLock(&lock)`, the same nine stores); written on the local itself the compiler turns the operands of the
  destination's sum and of the skipped rows' product around. A constructor in `TextureLock` gives the same match but
  moves two stack slots of `Context::LoadDebugFont` (0x1070FC90; any inline function body in dxtexture.h does).
- (op-map1) 0x1072B230 / 0x1072B470 unchanged (7.4 % / 13.8 %). Measured on reduced copies of the unit: with two nested
  loops whose outer counter is used inside the inner loop the compiler never passes the texture in a register (a single
  loop, or an inner loop that does not use the outer counter, gives edi; using the texture twice in the inner loop gives
  esi); no order of the parameters, counter types, loop forms, `if` / `else` layout, local for `count + 1` or bound read
  in the condition changes that for the real body.
- (op-finish) 0x1072B470 `DDSParser::Load` stays EQUIVALENT (13.8 %): it needs `UploadVolumeLevels` (0x1072B230) to
  take the texture in edi like the engine's (stack order stream, description, dropTop: the signature `(stream,
  description, dropTop, texture)` brings 0x1072B230's body to the engine's apart from ebx / edi), but this compiler
  never chooses a register parameter for it (no permutation of the four parameters does); `UploadLevels` (0x1072B050)
  does get its rect in edi. With that the stream would sit in ebx as in the engine.
- (op-map2) 0x1072B230 `UploadVolumeLevels` **matches**: each branch reads the level count itself
  (`unsigned int count = texture->info->description.levels + 1;` inside the dropTop branch, the plain count after
  it), as `UploadCubeLevels` does; one count read before the test is what kept the texture on the stack. The signature
  is the cube version's `(stream, texture, description, dropTop)` (the symbol is renamed); the texture then comes in edi.
- (op-map2) 0x1072B470 `DDSParser::Load` stays EQUIVALENT, now 22.6 % (was 13.8): the texture goes to the volume upload
  in edi; the stream stays in its argument slot where the engine keeps it in ebx. One more use of the stream right after
  the header read (a null test) gives it ebx and the engine's prologue, so its weight is what is missing; two upload
  calls in the 2D case and casts at each use do not add it.
- (op-map3) 0x1072B470 `DDSParser::Load` **matches**: the part is pointed at before its fields are set
  (`part = &rect; rect.y = height; rect.x = width; rect.width = ...; rect.height = ...;`); with the pointer taken after
  the fields the rect's stores take ebx and the stream its argument slot. Found with tools/permute.py over the six
  statements of the part's set-up; a barrier between the fields and the width check also gives the stream ebx (78 %).

## pure3d primitives: Mesh (src/mesh.cpp, 0x10707280 - 0x10707330), started

Mesh overrides slot 3 (`Draw`, 0x10707280, 5 arguments) and slot 7 (`FillBatch`, 0x10707330, 3 arguments) of
`Primitive` (whose layout in primitive.h is right: `LockableRefCounted` is 0xC bytes, so the flags sit at +0xC, the
type at +0x14 and the binding source at +0x18; Mesh's own members start at +0x1C). Matched:

- **The draw descriptor** is `pure3d::PrimDrawDesc` (0x4C bytes, `primstream.h`). The engine has three constructors:
  0x10611CB0 (8 arguments, the one `PrimStream::End` uses), 0x10611C30 (9, the one `Mesh::Draw` and `Skin::Draw` use)
  and 0x10611DC0 (10, the one `GpuSkin::Draw` uses); all three are declarations here, mapped in symbols.txt, and
  their argument orders differ. Map for the 9-argument one: `(void* format, const math::Matrix* world, int count,
  void** parts, PrimGroupList* list, int a, int b, int c, int d)`. **The 10-argument one fills a 0x54-byte object**:
  0x10611DC0 forwards its arguments 1 - 7 and 10 to the 8-argument constructor and then stores argument 9 at +0x4C
  and argument 10 at +0x50. That larger type is `pure3d::PrimDrawDescGpuSkin` (a `PrimDrawDesc` plus the two words,
  `primstream.h`), and with it `GpuSkin::Draw` matches 100 %; its argument order is the same as the 9-argument one's
  (`format, world, count, parts, a, b, c, kind, d, e`). The device call is `pddi->DrawPrimitive(shader,
  &desc, parameters)` (pddi slot 1) from Mesh and Skin, and `pddi->Unknown2(shader, &desc, parameters)` (pddi slot 2,
  `pddi.h`) from GpuSkin. The first member of the descriptor is the *vertex format* of the drawing object and is read
  at +0x10 of what `Primitive::unknown18`, `PrimitiveState::GetBindingSource()` or the part's binding point at
  (`PrimBufferOwner::format`); `GpuSkin::Draw` overwrites it from the part's binding after the constructor.
- **A `Mesh`'s own members**: `+0x1C` is a 32-bit word (the kind of primitive the batch carries; `FillBatch` copies
  only its low half into the batch's 16-bit +0x70, which the compiler does with a 16-bit load), then a
  `PrimGroupList*` pair at +0x20 / +0x24 (the groups and the list the batch is prepared through). A `Skin` has the
  same word at +0x1C (so `Skin::GetUnknown1C` is `?GetUnknown1C@Skin@pure3d@@QAEIXZ`, not `...PAXXZ`), a
  `PrimBuffer*` at +0x144 (a group to add and the buffer `UnlockBuffer` unlocks) and a `PrimGroupList*` at +0x148.
- **`PrimitiveState`'s slot numbering starts after `RefCounted`**: the vftable is [destructor, AddRef, Release,
  then the class's own virtuals], so `Unknown3` is slot 3, `Unknown9` is slot 9 (offset 0x24) and `SkinState::GetPose`
  is slot 10 (offset 0x28). `Primitive` is the same: `Draw` is slot 3 and `FillBatch` slot 7.
- **`Pose` is much larger than pose.h lays out** (0x138 is past `PoseData`); the skinning code stamps the word there,
  so `pose.h` carries a `PoseSkinView` for it.
- 0x1071EE50 `Skin::FillBatch` matches (skin.cpp). `*unknown` is set to true at the end in *both* paths, and the
  batch's +0x84 is a `bool` saying whether the state had a second pose to blend in — which is why `PrimBatch`'s
  +0x84 is declared as one.
- 0x1072DEC0 `GpuSkinState::GetBuffer` and 0x1072DF10 `GpuSkin::Draw` match (gpuskin.cpp). The draw builds
  `PrimDrawDescGpuSkin` (the 0x54-byte type above) as
  `(source->format, world, 1, &unknown138, unknown13C, 0, unknown1C, buffer[0x38/4], unknown140 + 8, 0)` where
  `source` is the state's binding source and `buffer` is `GpuSkinState::GetBuffer()`, then overwrites the descriptor's
  format from the part's binding when the caller passes one, and calls `pddi->Unknown2` (slot 2). The gpu skin's
  `GpuSkinState` keeps a buffer pointer at +0x1C
  whose word at +0x38 goes into the descriptor; `GpuSkin` itself is `Primitive` + the word at +0x1C + a
  `ShaderParameters` at +0x20 (0x118 bytes) + +0x138 (the device buffer) / +0x13C (its stream) / +0x140 (its index
  data, whose +8 goes into the descriptor) + three floats at +0x15C and an int at +0x16C.

NONMATCHING (this range):

- 0x10707280 `Mesh::Draw`: every instruction is the engine's except that the engine sets the descriptor's count and
  its parts pointer up *inside* each branch of the state test (`push 2` / `push 1`, the matching `lea`) and converges
  on a shared call to the constructor, while ours computes both before the branch and keeps them in registers; the
  shared-tail form needs one call site, the two-call-site form makes the compiler allocate two stack slots. 13 %.
- 0x1071ED50 `Skin::Draw`: the engine keeps the state in edi, the skin in esi, the binding source in ebx and the
  group count in ebp; ours assigns those four the other way round (state esi, skin edi, source ebp, count ebx) and no
  order of the locals changes it. 14 %.

- 0x10707330 `Mesh::FillBatch`. Lesson: **the batch a primitive fills is the object at `DrawablePart::batch`
  (+0xA0) and it is 0x88 bytes, not the 0x2C drawable.h keeps it as** — `+0x2C` is the part's world matrix and
  `+0x10C` / `+0x110` are the words after it, so the fields the primitives write at +0x28 and +0x70 - +0x84 are the
  same memory under other names. `PrimBatch` (a view, in primitive.h alongside `PrimGroupList` and `PartStateView`)
  names them; its +0x70 member is 16-bit, which is what makes the compiler copy it with `mov ax`. The state's group
  table is `state->groups[state->unknown38]` at +0x30 / +0x38 and must be written as an **array member** — through a
  pointer member the compiler loads the pointer first instead of folding it into `[ecx + edx*4 + 0x30]`. The two
  calls are `PrimGroupList::PrepareBatch(batch)` (0x106268B0) and `PrimGroupList::AddGroup(batch, group)`
  (0x10625910, note the argument order).
- Adding members to `PrimitiveState` in primitive.h moves every member of `MeshState`, `SkinState`, `GpuSkinState`
  and `ParticleSystemState`, which breaks 26 matched functions in the engine, pure3d and proto units. Use a view
  struct (`PartStateView`) instead.

## pure3d/geometry: the loaders (0x10B8B000 - 0x10BA0000), started

`pure3d::PrimGroupLoader` (RTTI; base `pure3d::RefCounted`, 3 slots, vftable 0x10EAF644, unit 0x10B8BD30 - 0x10B8C800)
and the loaders after it in the same code range: `PolySkinLoader` (vftable 0x10EAF784, LoadObject 0x10B90CA0),
`CompositeDrawableLoader` (0x10EAF8B4, LoadObject 0x10B91410) and `GeometryLoader` (0x10EB0314, LoadObject 0x10B9C3E0).
`PrimGroupLoader`'s layout, read off its constructor and destructor: the shader it draws with at +8 (released by
`core::SafeRelease<pure3d::Shader>`, 0x102CD490 — 0x10B8F1C0 finds it in the `LoadInventory` through
`DynamicCaster<pure3d::Shader>`), an int at +0xC, three flags at +0x10 - +0x12 (the second true), an int at +0x14 and
the pairs +0x18 / +0x1C (both -1), +0x20, +0x24, +0x28. Its methods, all reconstructed in primgrouploader.cpp/.h:

- 0x10B8BD80 `SetIndex(int)`: `unknown18 = value` (10 bytes).
- 0x10B8F1C0 `bool ReadGroup(ChunkReader*, LoadInventory*)`: the 0x10020 chunk only, reads the shader's name, finds
  the shader in the inventory (`Shader*` at +8) and then the group's own words.
- 0x10B8FFE0 / 0x10B8F400 / 0x10B8DFF0 `BuildGpuSkin` / `BuildSkin` / `BuildMesh(void* object, ChunkReader*,
  LoadInventory*)`: the three 0x10020 - 0x121305 chunk loops. 0x10B8FFE0 is the gpu-skin one (0x10B8BD90 makes the
  `GpuSkin` through 0x1072E3E0 and holds it in `object`).
- **0x10B90A70 `MakePrimitive(void* object, ChunkReader* reader, LoadInventory* inventory, bool skin, bool gpu)`
  matches 100 %** (130 bytes): `if (ReadGroup(reader, inventory)) { if (skin) { if (gpu) BuildGpuSkin(...) else
  BuildSkin(...); core::SafeRelease(shader); return; } BuildMesh(...); core::SafeRelease(shader); }` — note the
  `SafeRelease` and the `return` inside each branch, and that the third branch falls through. The two bools are the
  arguments the callers pass (`PolySkinLoader::LoadObject` passes `true` and the flag of the 0x1002B chunk).

`PolySkinLoader`'s own layout, from its constructor (0x10B90BD0): the vftable at 0, the `content::LoadObject` count at
+4, 0x10001 at +8, 0 at +0xC, a `true` byte at +0x10, -1 at +0x14, and a `PrimGroupLoader*` at +0x18 (0x2C bytes,
allocated by the constructor and set through 0x10B90B60). `PolySkinLoader::LoadObject` calls
`[this+0x18]->SetIndex([this+0x14])` and `[this+0x18]->MakePrimitive(&part, reader, inventory, true, flag)`.

- (op-add1) **0x10B8F1C0 `ReadGroup` matches**: the shader is looked up through an inline `FindShader(inventory,
  name)` that declares the `DynamicCaster<Shader>` and calls `FindObject(&caster, ObjectName(name, 1), true)` (its
  caster then shares the frame slot of the words read later, and the inventory's vtable stays in ebp); the result
  goes into the member first and then into a local (`shader = FindShader(...); Shader* found = shader; if (found == 0)
  { found = new Shader("error"); shader = found; } found->AddRef();`). Written straight through the member the
  compiler reloads it for the AddRef; with the local first it keeps the inventory in ebp and spills its vtable.
- (op-add1) **The three builders and their makers match**: 0x10B8C270 `CreateMesh`, 0x10B8C820 `CreateSkin`, 0x10B8BD90
  `CreateGpuSkin`, 0x10B8DFF0 `BuildMesh`, 0x10B8F400 `BuildSkin`, 0x10B8FFE0 `BuildGpuSkin`. Their real sizes include the
  switch tables (0x11CA, 0xBDE, 0xA86; functions.tsv had cut `BuildMesh` at 0x2DE and listed its case bodies as 17
  functions). The 0x38-byte object the makers give the states is `VertexOffsetList` (RTTI; primitive.h called it
  `Expression`). What it took, for the next loaders of this kind:
  - **VS2005 compiles a unit bottom-up and uses what it learnt about the callees it compiled**: with the makers defined in
    the unit the compiler knows they keep neither `&mesh` nor `&state`, so it caches both in registers after later
    calls as the engine does (declared only, it reloads them); with the `VertexStream` constructor and set-up defined in
    the header it knows the streams do not escape, so the loops walk `stream.current` and `stream.stride` in registers.
    The order of the definitions in the source does not matter.
  - The loops are `for (unsigned int i = 0; i < count; i++) { reader->Read(stream.current, ...); stream.Next(); }` on
    the stream's own cursor (a local pointer gives other load orders and, in `BuildMesh`, a switch index in eax).
  - **Frame slots of locals of 16 bytes or less follow their uses per byte** (most used per byte nearest esp); larger
    locals in disjoint scopes share a slot (all the streams, the three name buffers). One wrong size reshuffles the
    whole frame: the controller list is 12 bytes (`begin`, `end` and a third word the reader never sets), and `Half4`
    is 8-byte aligned (`__declspec(align(8))`, which also gives `BuildMesh` the engine's `and esp, -8` frame).
  - `CreateSkin` writes its three branches out in full (each up to `SetState`); a shared tail or a goto gives other
    registers. `BuildSkin` computes the three stream masks into locals (state, buffer, source) before the descriptions.
  - The half-float repack is `math::Vector vector = value.ToVector(); math::Vector copy = vector; Half4 packed;
    packed.Set(copy);` in a `__forceinline` helper taking `Half3` by value (with a member-wise copy constructor); the
    controller test is `Size() > 0` with an unsigned `Size()` (`!= 0` folds to a mask test).
  - Ties of equal uses per byte depend on the unit's symbol numbering: header declarations shift them in other units
    (0x1070FC90 `LoadDebugFont` moved and came back while these headers changed); re-check every includer.

Constructor:

- 0x10B8BD30 `PrimGroupLoader::PrimGroupLoader` matches (mp-load): the engine's copy keeps the vftable store of the base
  constructor it inlines (`mov [eax], 0x10DA05B0`, RefCounted's) between the count store and the class's own
  (`mov [eax], 0x10EAF644`) and loads the second shared constant register (`or edx, -1` for the two -1 members) only
  after the count store. `pure3d::RefCounted`'s constructor (entity.h) ends with `_ReadWriteBarrier()` after
  `mRefCount = 0`: the barrier keeps the stores of the base vftable and of the count and ends the scheduling region
  there, so the derived constructors' constants come after the count store. A call to an inline function or to a member
  object's constructor that does the count store has the same effect, but adds a declaration to the unit and moved the
  stack slots of 0x1070FC90 (`Context::LoadDebugFont`); the barrier changed no other function of the 43 units that
  include entity.h. The barrier is declared in entity.h itself (`extern "C" void _ReadWriteBarrier();` and the
  intrinsic pragma): including `<intrin.h>` there switches off the unit-local register conventions of every unit
  that includes the header (a static helper takes all its parameters on the stack again).

The chunk loaders of this range (the geometry, polygon skin, composite drawable, skeleton and the three shader loaders)
are reconstructed, one source file per unit under src/code/pure3d/loaders/:

- Matching: 0x10B9C3E0 `GeometryLoader::LoadObject`, 0x10B90CA0 `PolySkinLoader::LoadObject`, 0x10B96280
  `NewShaderLoader::LoadObject` (100 %).
- EQUIVALENT (the same calls, arguments, branches and memory accesses in the same order; they differ in registers,
  the order of the frame's variables and the scheduling of the reader's stream loads, and are replayed against the
  engine's function with random chunk streams and stubbed callees): 0x10B91410 `CompositeDrawableLoader::LoadObject`
  (42 %), 0x106DE090 `SkeletonLoader::LoadObject` (15 %), 0x10B95780 `ShaderTemplateLoader::LoadObject` (39 %).
  0x10706960 `ShaderLoader::LoadObject` (42 %) is NONMATCHING: on real states its draw parameters' bit word ends with
  other bytes than the engine's (difftest). What keeps them from matching: the engine keeps the inventory in ebp and a
  zero in ebx through the chunk loop (this compiler picks other registers), `ShaderLoader` keeps the draw parameters'
  bit word in esi and writes it through after each change, `SkeletonLoader` saves edi only inside its block and caches
  the joint's kind in cx, `CompositeDrawableLoader` releases the controller loader inside each branch and keeps the heap
  index in memory.
- Findings the units share: `container::ArrayDynamic<T, AllocatorNew>` is 16 bytes (begin, end, capacity, allocator) in
  the engine and its `Create` / `Allocate` store order differs; `pddiShaderInputInitData::SetBool` ... `SetDefault`
  (0x106138A0 - 0x10613990) take the input's name as `const char*` and build the `Name` themselves; the
  `LoadObject` virtual (slot 7) takes a `LoadInventory*` as its fourth parameter; `ChunkReader::BeginChunk` answers the
  chunk id; functions.tsv gives 1552 bytes for 0x10B95780 (the unit is 0x9E2 bytes of code and two tables).

- 0x102A6140 `proto::ShaderPalette`'s scalar deleting destructor (`??_GShaderPalette@proto@@UAEPAXI@Z`, 30 bytes)
  is compiler-generated: it calls `??1ShaderPalette` (0x102A60B0, 107 bytes, which walks and frees the two
  `container::ArrayDynamic` members at +8 and +0x18 and restores the `content::MetaLoadObject` vftable 0x10D96DB8)
  and then `content::LoadObject::operator delete` (0x105FE720). Counting it needs the class and its destructor
  reconstructed first, in `code/proto/shaders/`; the annotation itself can be written the way
  `engine/physics/physicsmanager.cpp` annotates eight generated `??_G` bodies (a block of `// FUNCTION: ENGINE`
  lines with no definition under it).
- 0x1072E3E0 `GpuSkin::GpuSkin(const ShaderParameters*, const IndexBufferDescription*, unsigned kind)` (259 bytes):
  the third session read the whole body and it is ready to write except for one call.
  `Primitive::Primitive(0x4000)` (0x106F2F20, not mapped yet), the vftable 0x10E5CFA0, `unknown1C = kind`,
  `ShaderParameters::ShaderParameters()` at +0x20 (0x102E8BB0, through the thunk 0x100428B1), `unknown140 = 0`,
  three floats at +0x15C - +0x164 zeroed, `unknown16C = -1`, `parameters = *arguments1` (0x10707B00),
  `unknown138 = context->NewVertexBuffer(arguments1)` and AddRef'ed (global 0x1127F358, 0x1061B600),
  `unknown13C = context->NewIndexBuffer(arguments2)` when `*arguments2 != 0` (0x1061B660), then
  `for (i = 0; i < parameters.unknown4; i++)`: `if (gName1127F1B8 == parameters.parameters[i].name)
  flags.Set(6, true); else if (gName1127F1DC == parameters.parameters[i].name) flags.Set(7, true);` — the entries are
  0x10 bytes apart from `parameters + 0x10`, and `flags` is the primitive's word at +0xC.
  **The blocker**: the engine's call goes through the incremental link thunk 0x10027318 to 0x102CC900, *this unit's*
  copy of `PartAnimationFlags::Set`, while the copy symbols.txt maps (`?Set@PartAnimationFlags@pure3d@@QAEXH_N@Z`)
  sits at 0x102E8B80 and calls its own unit's SetBit/ClearBit (0x102E8950 / 0x102E8970 against 0x102CC2A0 /
  0x102CC2C0). objcmp's target check follows the thunk and compares the addresses, so a `flags.Set(...)` written with
  the shared name is not a match; it needs a second, unit-local name for the copy the way
  `engine::ReleaseEffectRef` (0x10805910) stands for another unit's `core::SafeRelease`. That naming decision is left
  to the next session; the call is the only thing missing.

- (mp-load) 0x1067F4D0 `Loader1067F4D0::LoadObject` matches: the chunk dispatch is a `switch` (cases 0x7020001 and
  0x7021100 / 0x7021101), not an if / else-if chain: with the chain this compiler gave the entries' size temporary the
  register of the loaded object and split the object around the allocation, with the switch the object stays in ebp
  and the size is spilled as in the engine, and the frame slots come out in the engine's order. The entries are
  `Loaded1066F430Entries` (begin, end, capacity, the allocator's word) with the inline `Allocate` of
  `ArrayDynamicHeap` (begin = 0 only for an empty request; the failure path stores end and capacity 0; the success path
  returns), called as `loaded->entries.Allocate(count)`.
- (op-finish) 0x10B8BD30 `PrimGroupLoader::PrimGroupLoader` (now matches, see above).
- (mp-load) 0x106DE090 `SkeletonLoader::LoadObject` stays EQUIVALENT, now 79.9 % (was 15.1): the scalar values the engine
  keeps in registers or reloads once (the version, the three counts, the joint's kind and enabled word) are not
  address-taken locals in the engine but results of inline reads (`ReadWord`, a two-byte `ReadShort`: the value sits
  in the inline function's temporary and the local is a plain variable); with them the reader lands in ebp and the
  skeleton in esi as in the engine, the frame is its 0x2B0 bytes and the debug info pointer is declared after the
  skeleton's `AddRef`. What is left is the rotation of the volatile registers the temporaries take, which starts to
  differ at the joint name's length (`movzx eax` in the engine, `ecx` here), the position of the name's terminator
  store and of the `mov ecx, [reader + 0x284]` load relative to the pushes. difftest SAME.
- (op-map1) 0x106DE090 stays EQUIVALENT (79.9 %): reading the joint name's length into a byte and copying it into an
  `unsigned int` (as the other name reads do) gives the engine's `movzx eax`, but the extra local moves the byte slots
  and the frame (61 %); the local's name does not matter. 0x10B91410, 0x10706960 and 0x10B95780 not reworked.
- (op-map2) 0x106DE090 stays EQUIVALENT (79.9 %): the joint name read through an inline helper, with the length cast,
  through a nested `unsigned int` count, a local buffer pointer or the stream's Read called directly all compile to
  the same code.
- (mp-load) 0x10B91410 `CompositeDrawableLoader::LoadObject` stays EQUIVALENT (42.4 %, was 41.8): declaring the four
  pointers (controller, visibility, the two mixers) before the heap is saved, not after it is restored, moves the zero
  stores and the heap index into the engine's arrangement (the heap index in memory); what remains is the register
  choice (the engine keeps the inventory in ebp and a zero in ebx through the chunk loop, ours the inventory in ebx),
  the frame order of the three arrays and the pointers, and the position of the controller case behind the loop exit.
  Releasing the controller loader inside each branch (as the engine does) gives the engine's instruction count but a
  worse layout with the pointers moved.
- (op-map2) 0x10B91410 stays EQUIVALENT (42.4 %): the engine's zero stores for the four pointers come after the heap
  is restored (controller, visibility, the sub-drawable mixer, then the chunk mixer from edi), but declaring them
  there puts the heap index into ebp (41.8 %, in every declaration order).
- (mp-load) 0x10B95780 `ShaderTemplateLoader::LoadObject` stays EQUIVALENT (39.4 %): the engine's frame is 16 bytes
  larger (0x50C against 0x4FC); reading the sampler word into its own local instead of reusing `first` makes it 8 bytes
  larger but moves the stack slots away from the engine's. The engine tests the slot with `cmp [slot], -1; setne al;
  test al, al; jne`, this compiler folds every spelling of `IsValid()` into `cmp; jne`.
- (op-map2) 0x10B95780 stays EQUIVALENT (39.4 %): this compiler materialises a validity test as `setne al; test al, al`
  only when the bool has a second use (a test small enough to fold otherwise, in every spelling of IsValid); the
  default's test moved behind the inner loop as `if (!found && !slot.IsValid())` gives 43.3 % but still folds the
  first test, and the frame is still 16 bytes smaller. Not kept.
- (mp-load) 0x10706960 `ShaderLoader::LoadObject` stays NONMATCHING (41.8 %, instruction sequence 96 % the same): the
  engine caches the draw parameters' bit word in esi at the top of each chunk and writes it back after each change,
  this compiler loads it in every branch; with `Shader::SetParameters` taking the parameters by value the word is
  promoted to esi the same way, with a reference parameter (the engine's) it never is, whatever the loop contains.
- (op-map2) 0x10706960 stays NONMATCHING (41.8 %). The engine keeps the bit word in esi across the two Read calls of
  the 0x11003 case and loads it once at the loop head, so to the engine's compiler the parameters are not exposed to
  those calls, yet SetParameters gets the struct's own slot (no copy). Not reproduced: a copy before the call, a
  temporary, an inline wrapper taking the parameters by value (all copy), a `__restrict` pointer to them, `const`
  plus const_cast, `__declspec(noalias)` on the chunk stream's Read. The difftest difference is in bytes both
  functions leave uninitialised (the top byte of the bit word, bits 3-7 of the flag byte and the three bytes after it
  come from the stack), so it is not a behaviour difference, but the conversion needs SAME.
- (op-map3) 0x106DE090 stays EQUIVALENT (79.9 %): the length declared before the buffer, the skeleton name's byte reused
  for the joint names (61 %), a barrier after any statement (80.6 % after the terminator, not kept) and the orders of
  the joint chunk's first seven statements leave the register rotation. 0x10B91410 (42.9 % with a barrier at best) and
  0x10B95780 (43.2 %) not improved by barriers; 0x10706960 not reworked.
- (op-map4) 0x10706960 `ShaderLoader::LoadObject` stays NONMATCHING but goes from 41.8 % to 51.6 % of the bytes
  (493 of the engine's 617 instructions in its order, from 435) once `Shader::SetParameters` (0x107062D0) is compiled
  in the same unit: VS2005 looks at a callee it has already compiled in the unit and, when that callee only reads
  through the pointer or reference it is given, the caller's local does not count as exposed to the *other* calls,
  so the loader keeps the draw parameters' bit word in esi across the chunk stream's Read calls as the engine does
  (the callee being external, or a copy, restrict, const_cast and noalias spellings, never gave that). The same
  trick did not help 0x10720CF0 (its callee hands the pointer on to an external operator=). `SetParameters` is
  written (95.9 %: its two virtual GetTechniques calls take the vftable in eax and the slot in edx, the engine the
  reverse) but stays NONMATCHING: it needs `dxTechniques::IsEnabled` (0x10618560) declared, and a fifth member
  function of that class moves two locals of `Context::LoadDebugFont` (0x1070FC90) out of their slots (any member,
  whatever its name, type or place; removing one of the four restores them; the locals' names, types and declaration
  order in LoadDebugFont do not). `ShaderLoader::HasName` (0x107065C0) and `InputNames::At` (0x107065F0) **match**: the name table is a
  `container::Map<unsigned int, const char*>` over the global array new / delete (0x10706420 is its Insert, 0x10706070
  / 0x107060A0 its comparators, 0x107060C0 its deleter), `HasName` is `if (Find(code).node != 0) return true; return
  false;` (the `!= 0` as a plain bool gives `neg / sbb / neg`), `At` is Find, then Insert(Pair(code, 0)) when there is
  no node, and the address of the node's value. The loader's HasName / At being in the unit changed nothing more;
  left are one frame slot (0x4E4 against 0x4E0, the low region's slots are laid out differently) and the position of
  the 0x11003 case's SetFloat path.
- (op-eq1) 0x10706960 `ShaderLoader::LoadObject` is EQUIVALENT now (41.8 %; SetParameters stays out of the unit, so the
  engine's copy is called and no dxTechniques member is needed). difftest on its two captured states agrees on every
  call, argument, return and store except five bytes of the shader's parameters: the bit word's top byte, bits 3 - 7
  of the flag byte and the three bytes after it, which both functions copy from their own uninitialised stack
  (`PrimStreamParameters()` sets bits 0 - 23 and the three flags; the engine's Shader constructor and Init leave the
  same bits as the heap and the technique's record had them) and which nothing reads: the device's state applier
  0x10629E80 (reached from dxShader::Draw 0x1062A770 through 0x1062A340) masks bits 0 - 23 of the word and bits 0
  and 2 of the flag byte, SetParameters reads bits 0 - 9 and flag bits 0 - 1, the passes and the tracer the same
  fields; a false positive of the byte comparison, not a behaviour difference. The map's `CompareKey` (0x10706070),
  `CompareNodes` (0x107060A0) and `Insert` (0x10706420) instantiations are mapped in symbols.txt now (ours are
  byte-identical), so difftest compares the comparator argument of `TreeBase::Find` by symbol.
- (op-map4) 0x106DE090 stays EQUIVALENT (79.9 %, 538 of 628 instructions): compiling its unit's own callees (the
  Skeleton constructor 0x106DDF20, Finish 0x106DDAA0 and the SkeletonDebugInfo constructor) next to it changes
  nothing in it, so the register rotation is not the callee knowledge that moved the shader loader.
  `SkeletonDebugInfo::SkeletonDebugInfo` (0x106DD980) **matches** (six stores). The Skeleton constructor is written
  (15 %: the partitions' vector constructor and the joint masks' loop) but not kept.
- (op-map4) 0x10B91410 and 0x10B95780 stay EQUIVALENT (42.4 % / 39.4 %), not reworked: neither calls a function of
  its own unit (the callee-knowledge finding of the shader loader does not apply), and the template loader's 16
  missing frame bytes are not its local objects (the engine's constructors write 4 bytes of a `ConstantSlot` and 8 of
  a `pddiShaderInputInitData`, as declared).
- Findings (mp-load): (1) a unit-local function takes a parameter in a register only under conditions that depend on
  what it calls: with `UploadLevel` defined in the unit (unit-local, two register parameters, as in the engine)
  `UploadVolumeLevels` keeps its texture on the stack, with `UploadLevel` only declared it takes the texture in a
  register (ebx here, the engine's edi), and one more real use of the texture in its loops gives the engine's edi; no
  spelling of the same code found the engine's registers, so 0x1072B230 and 0x1072B470 stay as they are; (2)
  `#include <intrin.h>` in a header switches the register conventions of all unit-local functions of every unit
  that includes it off (use `extern "C"` plus `#pragma intrinsic` for a single intrinsic); (3) values the engine
  reads through an inline reader (`ReadWord`, `ReadShort`) are plain locals, `reader->Read(&local, ...)` makes them
  address-taken and changes the allocation of the whole function (SkeletonLoader 15 % -> 80 %); (4) a `switch` over
  the chunk id lays the case bodies and the allocation out like the engine's where an `if` chain does not
  (Loader1067F4D0); (5) a one-word `ArrayDynamicHeap::Allocate` as an inline member (early `return true`, `begin =
  0` only for an empty request) gives the engine's shared tails.

## fight/sequencer (src/code/engine/fight/, unit 0x105A2440 - 0x105A7BF0)

The sequencer a fight node runs (engine/fight/sequencer.h): the action list, the schedule clock and the node's track.
The classes are `fight::Action` (RTTI, 9 slots), `fight::Track` / `fight::Condition` / `fight::Item` / `fight::Param`
and fight::RefCounted; the sequencer class itself has no RTTI. 256 bytes of `Action::SetFlag`, `Sequencer::Clear`,
`Stop`, `Update`, `ConditionList::Evaluate` and `Action::End` / `Sequencer::SetTrack` / `Schedule` / `Track::Unregister`
match; Advance and the NPC unit's pose copy are EQUIVALENT.

Lessons (the important ones):

- **A one-bit `unsigned int` bit-field tested directly compiles to a mask test (`test al, 4`); testing it through an
  inline accessor that returns `bool` gives the engine's `mov ecx, eax; shr ecx, 2; test cl, 1`.** The value has to be
  materialised as 0/1, and only the accessor's `bool` return type forces that. Writing `(flags >> 2) & 1` by hand does
  *not* work: the optimiser folds it back into the mask test. A `bool` bit-field is wrong too (MSVC 2005 then loads the
  byte: `mov al, byte ptr [ecx + 0xc]`). The flag word is a union of the raw `unsigned int` and the bit-field struct,
  because the same code also masks it (`flags.all & (0x800 << arg)`).
- **A call to a function defined in the same source file lets the caller keep values in xmm across it** — the compiler
  knows the callee does not touch them, and the spill the engine makes disappears. `Sequencer::Advance` only reached
  90 % until `Action::SetFlag` moved to its own unit (action.cpp): with the body visible, our build kept `now` and
  `timeBegin` in xmm0/xmm1 across the call where the engine reloads both from the stack. The same applies to
  `fight::ReleaseRef`-style helpers: `core::SafeReleaseRef` (0x10098F90, one of the per-type copies of core's release
  helper that sit together at 0x10098F60 / 0x10098FB0 / 0x10098FD0) has to stay out of the sequencer's unit.
- `Sequencer::Advance` reuses its `dt` parameter for the scaled step (`dt = timeScale * dt;`), which is what puts the
  step in the argument's stack slot and `now` in the only fresh local.
- A `switch` on three values gives the engine's `sub ecx, 0 / sub ecx, 1 / sub ecx, 1` chain where an if/else-if chain
  gives `cmp`. `ConditionList::Evaluate` did not match until the op was written as a switch with case 0 last and
  falling through to the loop's tail, and the early `return true` became `if (condition != 0) { do ... } while (...);`.

## engine/fight/behaviours/fighttreebehaviour.cpp and its neighbours (0x10862A60 - 0x10864EF0)

112 functions. The range holds **four** units; the boundaries are read off the class statics and the vtables, not off
the address order (the two units interleave their statics):

| unit | range | identified by |
|---|---|---|
| `code/engine/render/behaviours/renderbehaviour.cpp` | 0x10862A60 - 0x108638BF | ctor 0x108636B0 and deleting destructor 0x10862C10 install `engine::RenderBehaviour` (vftable 0x10E730C8, 8 slots); 0x10862F60 / 0x10862AC0 are its reflection statics; 0x10863060 is the message handler and its switch bodies and jump tables run to 0x1086369F; the five small functions 0x10863850 - 0x108638B0 sit between the ctor and the fight unit's `GetClassInfo` and are the only ones whose owner is not certain (they read +0x3C / +0x8 and call through a slot) |
| `code/engine/fight/behaviours/fighttreebehaviour.cpp` | 0x108638C0 - 0x108642B7 | `GetClassInfo` 0x108638C0, ctor 0x108639E0 and destructor 0x10863AC0 install `engine::FightTreeBehaviour` (vftable 0x10E7311C, 8 slots); the debug dump 0x10863C50 and the message handler 0x10863FB0 carry the assert path `..\\..\\..\\code\\engine\\fight\\behaviours\\fighttreebehaviour.cpp` |
| frontend (a Scaleform/HUD unit, no class static) | 0x108642C0 - 0x10864C2F | the `fe_*` Lua natives (`fe_SetUpdateEnable`, `fe_ToggleHideHUDOption`, `fe_SetMouseVisibility`), the mouse-cursor and HideHUD statics at 0x111CEF38-0x111CEF48 / 0x11315C58-0x11315C70, and the Scaleform screen calls 0x10872AD0 / 0x10873220 / 0x108816F0 |
| path behaviour (IPathBehaviour / PatrolPoint / SplineBehaviour) | 0x10864C30 - 0x10864EF0 | the five class statics 0x10864C30 / 0x10864C70 / 0x10864CB0 / 0x10864D00 / 0x10864D40 naming `engine::IPathBehaviour`, `engine::PatrolPoint`, `engine::PatrolPathBehaviour`, `engine::SplineCV`, `engine::SplineBehaviour` |

Done: **47 functions match**, six are marked NONMATCHING (the rest were not attempted, so no body was written and
nothing was excluded from the build).

Fight unit, added by the third session: 0x108641E0 `GetMembers` (the member list: "fightBranch" through
`GetFightBranchRefMetaType` and "sequencer" through `content::GetClassMetaType<fight::Sequencer>()` /
`content::MemberOffset<fight::Sequencer>`), 0x10864180 (`engine::GetFightBranchRefMetaType<C>` - its **first
parameter is the class name the caller passes and never reads**, so the template takes a leading `const char*
unused`) and 0x10863A80 (`BaseClassCasterImpl<Behaviour, FightTreeBehaviour>`'s constructor, which the explicit
instantiation alone does **not** emit - it appears as soon as `GetMembers` declares `static
content::BaseClassCasterImpl<Behaviour, FightTreeBehaviour> sCaster;`, which is also how the path unit's 0x10864D90
can be had once `SplineBehaviour::GetMembers` exists).

- fight unit (12): 0x108638C0, 0x10863950, 0x10863970, 0x10863980, 0x10863A90, 0x10863AC0 (`~FightTreeBehaviour`:
  `core::SafeRelease(params)`, `sequencer.End()`, then `branch->Unregister(&branch)`), 0x10863B90, 0x10863BA0
  (`SetBranch`: the register / unregister pair, then `dynamic_cast<engine::PlaybackSet*>` and the owner), 0x10863F40 /
  0x10863F60 / 0x10863F70 (`FightBranchRefMemberGetSetter<FightTreeBehaviour>` ctor / Get / Set - its own explicit
  instantiation in `src/code/engine/fight/fightbranchref.h` brings them out of line) and 0x10863F90 (`??_G`).
  0x10863990 is **not** `FightTreeBehaviour`'s own slot 0 any more: the class does not override `Behaviour::Slot0`,
  so that byte is this unit's kept copy of the base's; the fight unit's vftable slot 0 holds the incremental link
  thunk 0x1002C0C5, which is how `symbols.txt` maps `?Slot0@Behaviour@engine@@UAEXXZ`.
- fight unit, NONMATCHING:
  - 0x10863900 `Slot1`: the parameters load and the two generator steps' registers, 54 %.
  - 0x108639A0 `GetParams`: the parameters load and the handle copy swap places, 89 %.
  - 0x108639E0 constructor: the vftable store and the sequencer's `this` swap places, 97 %.
  - 0x10863B00 `OnPostedMessage`: the two ids' blocks come out in the other order and the chain walk is rotated,
    23 % of 142 bytes (the middle - the check order, the `sete`/`test` pair the answer flag is built from and the
    `movzx` + 32-bit id comparison - is already identical; the source is in the file, behind the ifdef).
- `src/code/engine/gameobject/behaviours/pathbehaviour.cpp`: 0x10864DF0 `SplineCV::SplineCV` (seven floats and a
  flag), 0x10864E30 `~SplineCV`, and 0x10864FA0 (the caster's `IsDerived`).
- `src/code/engine/frontend/frontend.cpp` (20, new): 0x108642D0 `fe_SetUpdateEnable`, 0x10864310 `SetFrontend`,
  0x10864330 `GetFrontend`, 0x10864340 `GetFrontendHeap`, 0x10864390 `SetScreenCentre`, 0x10864420 `GetScreenWidth`,
  0x10864430 `GetScreenHeight`, 0x10864440 `UpdateScreenCentre`, 0x10864490 `SetCursorFade`, 0x108644A0
  `GetCursorFade`, 0x108644E0 `SetCursorScale`, 0x108644F0 `GetCursorScale`, 0x10864500 `ResetCursorScale`,
  0x10864520 `GetScreenCentreX`, 0x10864530 `GetScreenCentreY`, 0x10864560 `ShouldHideHUD` (returns `int`, not
  `bool` - with `bool` the compiler emits `mov al, 1` where the original has `mov eax, 1`), 0x10864590
  `fe_ToggleHideHUDOption` (a `^= 1`, `!flag` compiles to `cmp`/`sete`), 0x10864AE0 `ResetLanguage`, 0x108649F0
  `SetLanguageName` and 0x10864A00 `GetLanguageName` (the `core::Name<core::CaseSensitiveKey>` at 0x11315C78). The
  unit has no assert path and no class static, so the file name, the free-function shape and every name are guesses.
- `src/code/engine/gameobject/behaviours/pathbehaviour.cpp` (7, new): the five reflection statics 0x10864C30,
  0x10864C70, 0x10864CB0, 0x10864D00, 0x10864D40, plus 0x10864DF0 `SplineCV::SplineCV` (seven floats at +4 and the
  byte at +0x20) and 0x10864E30 `~SplineCV`. File name and header are guesses too.
- `src/code/engine/frontend/frontend.cpp`, more: 0x108642C0 (`FrontendObject::GetUnknown5C`, the member at +0x5C),
  0x108642E0 `CreateFrontend` (`operator new(0x1238, sFrontendHeap)` then the object's constructor), 0x10864350
  `SetScreenFlag` (the flag array at 0x11315C58 and `SetScreenValue` 0x10881340) and 0x108643B0
  `SetScreenClampedFloat` (the `!= 0` test is the two-`comiss` form, and the clamp is `math::Clamp`, which inlines
  `Select`'s subtraction: the `-120` is 0x10E73254 and the `120` 0x10DA57E0, both namespace-scope `const float`).
  NONMATCHING here: 0x10864540 `fe_EnableCatchupBehaviour` (57 %: the argument is pushed before `GetFrontend()` is
  called) and 0x108645A0 `ShutdownFrontend` (98 %: the instruction stream is the same, two bytes of the encoding
  differ).

Not done, by unit (each is a place to start, not a verdict):

- **fight unit**: 0x108639D0 (`[ecx+8]` getter - the owner is at +4 and +8 is `Behaviour::state`, so this is probably
  a method of another class in the file: `fight::Params::value` (+8) and `fight::Sequencer::track` (+8) are the two
  candidates this unit knows); 0x10863B00 `OnPostedMessage` (type 0xb: id 8
  reads a branch at +0xC, compares its slot 6 (`+0x18`) with `branch`'s and walks `sequencer.track`'s `+0x18` chain
  into the bools at +0x10 / +0x11; id 0x10 writes `GetParams()` into +0xC when it is 0, so the two ids are two
  message classes with a payload at +0xC); 0x10863FB0 `OnMessage` (384 bytes: type 2 ends the sequencer, type 0xb
  id 2 runs the branch / pending track with `fight::Track::Slot10` at `+0x28`, id 0xE calls 0x10863C50 itself, as
  `Dump(this + 0x18, message[0xC], true, 0)`); 0x10863C00
  (a `core::Name<CaseSensitiveKey>` lookup in `engine::gLoadListeners`' `Find` (0x105A4F90) followed by the `+0x8C`
  member's method 0x105A3690 - both of the sequencer's unit); 0x10863C50 (the "Fight Pre " dump: `Dump(Sequencer*,
  bool children, bool header, int indent)`, its Report calls are `core::Report(0, "Fight Pre ", file, line, 0, format,
  indent * 4, "", argument, 0)` with one `static bool sEnabled` per site, and the lines are 0x130 / 0x134 / 0x13b /
  0x141 / 0x142 / 0x155 / 0x162); 0x10864180 + 0x108641E0 (`GetMembers`: the members are named **"fightBranch"** and
  **"sequencer"**, the base is `content::GetClassMetaType<engine::Behaviour>()` and the caster
  `BaseClassCasterImpl<Behaviour, FightTreeBehaviour>`; the getter/setter pair is `GetBranch`/`SetBranch` with the
  code string at 0x10D94FF4; the sequencer's meta type is `content::GetClassMetaType<fight::Sequencer>()` and its
  offset is `content::MemberOffset(&((FightTreeBehaviour*)0)->sequencer, 0x18)`).
- **render unit** 0x10862A60 - 0x108638BF: **nothing attempted**. 0x10863060 is a `switch` whose case bodies and jump
  tables run to 0x1086369F although `functions.tsv` says 52 bytes (see the note below), and 0x10863850 - 0x108638B0
  are five 4 - 20 byte functions that read +0x3C / +0x8 and call through a slot. 0x10862AC0 is the reflection helper
  of the unit: `NamedReferenceMemberGetSetter<engine::RenderBehaviour, engine::render::DrawableArchetype>` (vftable)
  plus `content::LoadInventory::DynamicCaster<engine::render::DrawableArchetype>` and 0x105FF030.
- **frontend unit**: 0x108644B0 / 0x108644C0 / 0x108644D0 (5-byte `jmp` thunks - linker artefacts, leave them),
  0x10864600 (1007 bytes), 0x10864A20 `SetLanguage`, 0x10864AF0 (init, 308 bytes; it registers the `fe_*` natives
  through 0x102893A0 / 0x10280020 / 0x1036BA70 and calls `engine::LuaScriptManager::AddFunction` / `SetOwner`).
- **path unit**: 0x10864CF0 / 0x10864D80 / 0x10864DE0 / 0x10864E40 / 0x10864E50 (1-byte `ret`) and 0x10864DD0 /
  0x10864EC0 (`ret 8`) - vtable fillers or kept copies of header-defined members, not writable source; 0x10864D90
  (kept copy of the `BaseClassCasterImpl<IPathBehaviour, SplineBehaviour>` ctor - the same problem as 0x10863A80);
  0x10864DA0 (`engine::PatrolPoint` ctor: vtable 0x10E7335C at +0 and `container::String::vftable` at +0x1C - the
  member is a `container::String`, which our header declares abstract, so it needs a concrete spelling first);
  0x10864DB0 / 0x10864EA0 (`GetScriptManager()->Unregister(&static)` for 0x11315C98 / 0x11315C9C - most likely the
  compiler's atexit destructors of two file-scope statics whose class unregisters itself, which is the cheapest way
  to write them); 0x10864E60 (`FindGameObject(name, "")` (0x107F0170) then 0x108679D0 then
  `dynamic_cast<SplineBehaviour*>`: the second argument is 0x10D95365, and **the address is both** - the engine's
  `FindGameObject` is matched and types that parameter `const ObjectName&`, so the call site passes the object at
  0x10D95365, while the `Report` sites of the fight dump push the same address where a `const char*` is expected
  (its first byte is 0, so it reads as `""`). Declaring an `extern const content::ObjectName` at that address and
  using `""` in the reports reproduces both instruction streams without having to decide which it is);
  0x10864ED0 (`mov eax, [ecx + 0x1C]`, a *value* not an
  address) and the `container::ArrayDynamic<T>` members 0x10864EE0 - 0x10864F90 and 0x10864FD0 - the two
  instantiations are `ArrayDynamic<engine::PatrolPoint*>` and `ArrayDynamic<engine::SplineCV*>` (the RTTI names in
  classes.tsv), and they are inline template members: annotate them only if the instantiation can be forced out of
  line.
  The five `GetClassInfo`s prove the file owns `engine::IPathBehaviour` (vftable 0x10E734AC, 15 slots),
  `engine::PatrolPathBehaviour` (0x10E733FC, 16) and `engine::SplineBehaviour` (0x10E73454, 16).

### What the next agent needs to know

- **`functions.tsv` sizes are wrong inside 0x10863060.** The table says 52 bytes, but the function is a `switch`
  whose case bodies and its two jump tables run to 0x1086369F - the region is a hole in Ghidra's function map, not
  data. `symbols.txt` entries in this range must take the size from the disassembly; a truncating size makes
  `split.py` cut a target object that can never match.
- **`engine::FightTreeBehaviour`'s layout**: `Behaviour` (12 bytes: vftable, owner +4, state +8, flags +9,
  requested +0xA, timeSliceFrameSkip +0xB), then branch +0xC, two unknown dwords +0x10 / +0x14, the
  `fight::Sequencer` at +0x18, and the context pointer at +0x60. `fight::Sequencer` is 0x44 bytes (its constructor
  0x105A4020 inits 0x00-0x43: a `core::Name` at +0, then zeros, timeScale 1.0f at +0x34, clock at +0x38), so the
  four bytes at +0x5C are a member of the behaviour that no function in this range touches.
- 0x10863900 (vftable slot 1) stores the owner handle in the context and advances the engine's two 16-bit random
  streams (0x111BDA0C) - `(x & 0xffff) * 0x9069 + (x >> 16)` and `* 0x4650`. 0x10863950 (slot 3) calls
  `Behaviour::OnActiveChanged` and, when deactivating, `fight::Sequencer::EndPending` (0x105A3EC0, mapped in
  `symbols.txt` with that guess name - the sequencer's own unit should take it over).
- `FightTreeBehaviour::SetBranch` (0x10863BA0) is `if (branch != b) { if (branch) branch->Unregister(&branch);
  branch = b; if (b) b->Register(&branch); }` followed by `dynamic_cast<engine::PlaybackSet*>(b)` and a tail call
  into 0x108B0880 with the owner. `branch` is therefore an intrusive member: its destructor is what
  `~FightTreeBehaviour` (0x10863AC0) runs last, after `core::SafeRelease` of the context (0x1007F0F0) and the
  sequencer's cleanup (0x105A44A0).
- 0x10863B00 takes the `*_AVPlaybackSet_engine_*` debug statics at 0x111CEEC0 and 0x10863C50 writes them; they are
  the tree's "Fight Pre" dump, whose free-text messages are `""` in this reconstruction.
- 0x108644B0 / 0x108644C0 / 0x108644D0 are 5-byte `jmp` thunks in the middle of `.text` (targets 0x10881220 /
  0x10881290 / 0x108812B0): linker artefacts of the original incremental link, not source functions - leave them.
- **A kept copy of a header-defined template member can be matched with an explicit instantiation.** The original
  keeps `content::BaseClassCasterImpl<B, D>::IsDerived` out of line (it takes its address for the meta type's caster);
  `template struct content::BaseClassCasterImpl<IPathBehaviour, SplineBehaviour>;` in the unit's source makes the
  compiler emit the same 0x24 bytes at 0x10864FA0 (and the fight unit's at 0x10863A90, from `template struct
  content::BaseClassCasterImpl<Behaviour, FightTreeBehaviour>;`). Its **constructor is not emitted this way** - an
  explicit instantiation does not instantiate the implicit default constructor - so 0x10864D90 / 0x10863A80 still
  need either a user-provided `BaseClassCasterImpl()` in `metatype.h` (which would touch every unit) or a different
  route. The same trick should work for the `container::ArrayDynamic<T>` members of the path unit
  (0x10864EE0 - 0x10864F90, 0x10864FD0) once the element types are known.
- **`FightTreeBehaviour`'s `branch` is a `fight::Branch*`, not a `fight::Track*`.** `SetBranch` (0x10863BA0) hands
  it to `__RTDynamicCast` with the source type descriptor 0x1103DA18 = `.?AVBranch@fight@@` and the target
  0x111CEEB8 = `engine::PlaybackSet` (`engine::PlaybackSet : fight::Branch; fight::Entity; ...`), and `fight::Track`
  is a different class (`.?AVTrack@fight@@`, vtable 0x10E2CD54, 16 slots). The `?GetBranch@FightTreeBehaviour@engine@@
  QBEPAVTrack@fight@@XZ` name in `symbols.txt` and the `fight::Track* branch` member of the header are stale guesses:
  the bytes of 0x10863B90 (`mov eax, [ecx + 0xC]; ret`) do not change, but the declaration should become
  `fight::Branch*` once that class is declared. `fight::Branch` has 18 vftable slots (vtable 0x10E2C294) and the
  three slot numbers this unit uses are 6 (`+0x18`, returns what the message carries a copy of), and 10 / 11
  (`+0x28` / `+0x2C`, the run and the start of a track on a sequencer).
- **0x11331DFC is an IAT slot**, not engine data: `call dword ptr [0x11331DFC]` after `__RTtypeid` is
  `type_info::_name_internal_method(&__type_info_node)`, i.e. `typeid(*p).name()`. The slot table can be resolved
  from the import libraries the relinker writes to `build/<VERSION>/relink/*.def`: the .def line number minus 2 is
  the import's index in its DLL and the slot of index *i* is the one 0x10A88356-style thunk of that import points
  at, offset by 4*(i-1). `msvcr80.def` index 9 (line 11) is
  `?_name_internal_method@type_info@@QBEPBDPAU__type_info_node@@@Z`, and index 8 (line 10, `__RTDynamicCast`,
  slot 0x11331DF8) is the anchor: 0x11331DF8 - 4*7 = 0x11331DDC is index 1. This is how to name any bare
  `call dword ptr [0x11331xxx]` in the range without guessing.
- `0x10D95365` is the empty string (its first byte is 0), so a `core::Report` format of `"%*sFight Context: %s"`
  takes `(indent, "", name)` and `%*s` with `0x10D94FF4`-style codes is how the reflection member table prints.

### The third session's findings (strings, message layouts, the dump)

- **The range's string constants** (`python tools/disasm.py --bytes` reads data too): 0x10D94E7C `"pn"`,
  0x10D94FF4 `"p"` (the code of a *reference* member - both the fight tree's `fightBranch` and the render unit's
  `drawableSource` pass it), 0x10D97FAC `"GameObject"`, 0x10D97FA0 `"sequencer"`, 0x10E73144 `"%*s}"`,
  0x10E7314C `"%*s{"`, 0x10E73154 `"%*s%s"`, 0x10E7315C `"%*sStart branch is %s"`,
  0x10E73174 `"%*s<%s> doesn't have a branch to run."`, 0x10E731E8 `"%*sFight Context: %s"`, 0x10E09CC4 `" "`.
- **`0x10863C50`'s signature is `Dump(fight::Sequencer* sequencer, bool children, bool header, int indent)`**
  (`ret 0x10`), called from `OnMessage` as `Dump(&sequencer, message[0xC], true, 0)`. Its `static bool` report
  flags are seven consecutive bytes **0x111CEED9 - 0x111CEEDF** (0x111CEEDF = the line-0x130 site, then 0x134,
  0x13b, 0x141, 0x142, 0x155, 0x162 - i.e. **the addresses run opposite to the source order**, as MSVC assigns its
  statics), and `OnMessage`'s type-0xE site has an eighth at **0x111CEF32**. Everything it walks hangs off the
  sequencer: `sequencer[+8]` is the track (`Sequencer::track`), `sequencer[+0x3C]` a list whose nodes link at
  **+8** and whose vtable slot 3 (`+0xC`) answers the child `Sequencer*` the dump recurses into - that is
  `Action::GetChild`, so **`Action`'s list link is at +8, not at +4** as `sequencer.h` has it, and `Action`'s +
  `vftable` slot 3 (`+0xC`) returns a `Sequencer*`. `sequencer[+8]` is a `fight::Track*` (the id-8 message's +0xC
  is compared with it directly), and the dump's `start->Slot6()` result is discarded, so that call is a
  statement of its own.
- **0x10864130 sits in a `functions.tsv` hole** between `OnMessage` (0x10863FB0, which ends at 0x10864130) and the
  reflection helper: 0x50 bytes, `this->SetBranch(gLoadListeners->Find(ObjectName(text, 1))[+0x8C] -> 0x105A3690())`
  - the `PlaybackTreeBehaviour` message that names the branch to run. `split.py` needs a `symbols.txt` entry with
  its size before it can be carved out.
- `0x10863C00` is a two-argument **free** function that builds an `ObjectName(text, 1)`, finds it through
  `engine::gLoadListeners` (0x105A4F90) and returns `found[+0x8C].Method(arg1) != 0` (0x105A3690); it is *not* a
  boundary function of this unit (its `arg1` is at `[esp+4]` after the callee-cleaned `Name` constructor).
- The `content::BaseClassCasterImpl` constructor trick (see the fight unit's entry above) is the general answer to
  the "kept copy of a template member" problem: **an explicit instantiation emits the virtual members, and a
  declared object of the type is what makes the compiler emit the constructor**.

## proto/navmesh.cpp (proto::NavMeshHull, 0x10568390 - 0x105691D0)

The navigation mesh (global 0x112730C0) is `proto::AmbientNavMesh`; the hull class, its 28-byte edge records and the
area records are guesses. `AreaHeight` (0x10568390) matches; `Contains` and `HasOpenArea` are EQUIVALENT (register
roles of the loop index / cursor swapped).

- **The hull test is a 2D cross product in the XZ plane**, not XY: the point's `y` is never read in the loop and the
  two `vertices[a * 3]` reads are `+0` and `+8` (x and z).
- **A helper the unit calls has to be defined in that unit**, or the compiler cannot know it leaves the globals alone
  and reloads them every iteration. `HasOpenArea` reloaded `gNavMesh` inside the loop until `AreaHeight` was defined
  next to it (which also let the `fldz` / `xorps` zero constants hoist out of the loop); it went from 36 % to 73 %.
- A loop over a member array matches better with the base cached in a local (`NavEdge* edge = begin; int count =
  end - edge;`): that is what produces the engine's `mov edi, [ecx] / mov ecx, [ecx + 4] / sub ecx, edi` and the
  `edi + 4` cursor.

## Other units touched

- `pure3d::Camera::Contains` (0x106DCC20, src/code/pure3d/camera.cpp): the view volume test (a frustum of four planes
  in the first branch, an axis-aligned box around the world minimum 0x10D94664 in the second). EQUIVALENT — the engine
  merges both branches' failing exits into one block and cross-jumps their last test.
- `container::TreeBase::Find` (0x106109C0, src/code/container/treebase.cpp) and
  `proto::NPCInstanceManager::Update` / `NPCInstance::UpdatePose` (0x10479B10 / 0x10476A50,
  src/code/proto/npcinstancemanager.cpp) match except UpdatePose (EQUIVALENT: the engine loads the destination pose
  between the source test and its branch).
- `engine::Display::GetWidth` (0x10616130) and `engine::GetStreamHullPool` (0x108C7750) are one-accessor guesses
  placed in their own units; the 0x10616xxx region is one large class (offsets up to 0x82C), so the small accessors
  the linker scattered between its functions may belong to others.

## effects: particle update code and bullet tracers (pure3d/effects/src/*, proto/render/bullettracer.cpp)

Particle system states (`pure3d::ParticleSystemState`, a 0x4C4-byte object whose layout is now spelled out up to the
tables it reads), the update task that advances them, the generators' attribute arrays, the update kernels and the
bullet tracer's ribbon drawing. The units are guessed from the address ranges and the class names (the one path the
original gives is `code/pure3d/effects/src/particles.cpp`); `particlekernels.cpp` is 0x107836D0 - 0x10791D00,
`particlegeneratorupdate.cpp` 0x1079C000 - 0x107A0600, `particleupdate.cpp` around 0x1073F400, `particlearray.cpp` around
0x10740000 - 0x10748800.

| Address | Function | Status |
|---|---|---|
| 0x10748980 | ParticleArray::MultiplyAdd (particlearray.cpp) | match |
| 0x1079CE80 | ParticleAttributes::Apply | match |
| 0x1073FD30 | ParticleSystemState::BeginUpdate (particleupdate.cpp) | EQUIVALENT (86 %: the camera position is copied through x87 for its first component) |
| 0x1079F320 | ParticleSystemState::UpdateBounds | EQUIVALENT (31 %: the engine keeps the box minimum x in a register through the loop) |
| 0x1079F570 | ParticleSystemState::UpdateParticles (the task body; 3488 bytes) | EQUIVALENT (every call, argument and store identical by emulation; 14 %) |
| 0x10709D60 / 0x10709D70 | ParticleSystemState::GetTransform / GetGeneratorUnknown10 | match |
| 0x107837F0 | UpdateFrameBlend (particlekernels.cpp) | EQUIVALENT (94 %: SSE register numbers) |
| 0x1078B550 | UpdateNothing (a kernel that does nothing) | match |
| 0x100D5AC0 | math::AABB::GetSphere (math/src/aabb.cpp, a kept copy) | EQUIVALENT (9 %: the emptiness test keeps the far corner in a register) |
| 0x10625AC0 | dxVertexDeclaration constructor (pddi/src/dx9/dxvertexdeclaration.cpp) | match |
| 0x102E8BB0 | ShaderParameters constructor (src/mesh.cpp) | match |
| 0x1007EE60 | core::Name<CaseInsensitiveKey32> default constructor (core/src/name.cpp, a kept copy) | match |
| 0x102CFF50 | proto::BulletTracer::DrawLayer (6686 bytes; the ribbon of one layer) | EQUIVALENT (6 350 of 6 686 bytes, identical output by emulation) |
| 0x102CCCF0 | proto::ScaleColour | EQUIVALENT (two operand/register choices) |
| 0x102CD130 | BulletTracerState::GetWidthFade | match |
| 0x102CDE90 | BulletTracerState::GetFade | match |
| 0x102CDFB0 | BulletTracerState::GetDistanceFade | EQUIVALENT (the engine spills the age twice) |
| 0x102CD7F0 | math::pddiColour(const Colour128&) (a second copy of the Vector4 one at 0x102CD6D0) | EQUIVALENT (clamp test order, as 0x102CD6D0) |
| 0x102CFF00 | std::sort<float*> | match |
| 0x102CCEB0 / 0x102CCEF0 / 0x102CCF30 / 0x102CCF70 | BulletTracerState::GetInverse{FadeOutTrail,FadeInTrail,ShrinkOut,ShrinkIn}Time (callees of the tracer) | match |
| 0x102CCFB0 | BulletTracerState::GetTrailFade (callee of the tracer) | match |
| 0x102CE4D0 ... 0x102CFDD0 | the 13 other instances of VS2005's `<algorithm>` for float* that std::sort needs (`_Sort`, `_Median`, `_Med3`, `_Unguarded_partition`, the heap functions) | match |

The tracer unit's own `pddiColour(const Vector4&)` call is the copy in particlemanager.cpp; both copies are the same
code, and the one at 0x102CD7F0 belongs to `Colour128` (RTTI `math::Colour128`).

Matching notes:

- The compiler (VS2005) unrolls a simple counted loop by four: a plain `for (; dest < limit; dest += 4)` body of four
  statements gives the 16-element loop with the `(end - begin + 15) / 16 >= 4` guard and the one-group remainder loop
  (ParticleArray::MultiplyAdd). The bound must be a local (a member read each time keeps the loop rolled).
- A float function that sets its result in several branches and returns it is spilled to the stack at each
  assignment; a single ternary (`return time != 0.0f ? 1.0f / time : 0.0f;`) or a result variable assigned last
  avoids that.
- Float expressions are re-associated under /fp:fast: `a * b / c * d` and `x*x + y*y + z*z` come out in a different
  grouping than written. Separate statements pin the order (`float scaled = inv * age; ... scaled / age * x`, and
  `sum = dx * dx; sum += dy * dy; sum += dz * dz;`); a differential emulation of old against new code at both x87
  precisions (24 and 64 bits) found three functions whose first versions rounded differently.
- Clamp chains: a ternary chain with `math::Clamp` and `!(0.0f > t)` reproduced `GetFade`; for `GetTrailFade`, declaring
  the identity value (`float grow = 1.0f;`) right after the first clamp fixed the register order.
- `0.0f != f()` and `f() != 0.0f` compile to different `fucompi` operand orders; a comparison written `x <= 0` instead
  of `!(x > 0)` changes what a NaN does (the engine returns early on NaN).
- A float to `unsigned int` conversion is `fistp qword` with a control word change; the conversion of an unsigned
  loop counter to float is `fild` plus a fixup for the sign.
- A callee that is compiled in the same unit keeps its caller's `ecx`/`edx` live; the tracer's seven small helpers had
  to be reconstructed for `DrawLayer` to see them as such. The default `Name` constructor (0x1007EE60) must stay in
  another unit, or the loops that construct 16 shader parameters keep their zero in `edx`.
- The compiler inlines the sort wrapper into `DrawLayer` where the engine (inlining budget) did not: calling it through
  a function pointer (`void (*sort)(float*, float*) = std::sort<float*>`) reproduces the call.
- Ghidra's function sizes cut some epilogues (0x1079F320 is 577 bytes, not 570; 0x102CFF50 is 6686); the sizes in
  symbols.txt for these are the real ones.
- Dynamic casts to the generator classes (`dynamic_cast<ParticlePointGenerator*>`) need the RTTI type descriptor
  addresses mapped in symbols.txt (`??_R0?AV...@8`).


## pure3d render passes (pass/src/pass.cpp, pass/src/protopasses.cpp and the neighbours they call)

The passes of the render pipeline derive from `pure3d::Pass` (vftable 0x10E5E4D0, nine slots). Slot 4, which the first
reconstruction called a pure `Prepare`, is `Render(PassContext*)`: `Pass::Run` (0x10754AF0) saves the render states the
mask at +0x10 names, calls it, restores them, and `RunChildren` (0x10754B60) runs the children through the sibling
link. Slot 8, which asks the scene which parts the pass draws, is `GetParts(Scene*)` and answers a begin / end /
capacity triple (`PartList`); the filter it applies is the `PassEntries` at +0x28 (a word and sixteen 8-byte entries,
the engine's `container::ArrayFixed<PassEntry, 16>`; the shadow pass keeps a second filter at +0xC0 and swaps it in
around its first query). What the passes draw are `DrawablePart`s (0x12C bytes): the primitive at +0x90, its state at
+0x94, the binding at +0x98, the 0x2C-byte batch the device draws at +0xA0, the joint matrix at +0x50 and the world
matrix at +0xCC; render bit 9 says whether the batch or the primitive draws it. The passes write the shader
constants straight into the device's constant table (`pddi->constants->values[slot]`, the group bit of
`constantsDirty` first); the slot indices are globals filled by the static initialisers 0x10D6C000 - 0x10D70000, and
their names (`p3dPRLight_Colour2`, `p3dShader_LODGeo`, ...) come from the strings those initialisers hash
(`shaderconstants.h`).

| Address | Function | Status |
|---|---|---|
| 0x10754AF0 / 0x10754B60 | Pass::Run / RunChildren | match |
| 0x10610240 | PassEntries::~PassEntries (an ArrayFixed destructor in another unit) | match |
| 0x10766000 / 0x10766040 / 0x10766090 | ConstructCopiesN<PassEntry>, ArrayFixed<PassEntry, 16> copy constructor / operator= | match |
| 0x1076BE40 | ArrayFixed<Light*, 8>::PushBack (the engine calls it at two of the lit pass's six sites) | match |
| 0x1061C480 | pddiSurface::GetHandle | match |
| 0x10715910 / 0x10715AC0 | ShadowRenderManager::Get / the function that does nothing (unit shadowrendermanager.cpp from the asserts) | match |
| 0x10717920 - 0x10717980, 0x10717990, 0x107179D0 | LightSelection accessors and the user data scales (the per-draw light selection, global 0x112817D8) | match |
| 0x1074EE10 | RenderParams::GetUnknown14 | match |
| 0x102D3D30 / 0x106DEF20 | DrawablePart::GetBindingSource (a kept copy) / UpdateBatch (the "RootPass method" of the work list) | match |
| 0x10761750 | DrawablePart::Draw (batch or primitive by render bit 9) | match |
| 0x10204C10 | core::BitField<unsigned short>::Test (kept copy) | match |
| 0x1076AF90 / 0x107678C0 | ViewPass::GetUnknownE4 / ProtoShadowPass::GetShadowParts | match |
| 0x1076B020 / 0x1076B030 | ProtoLitPass::HasShadowMap / UploadVertexLights | match |
| 0x1076F010 | ProtoSlowZPass::Render | match |
| 0x1076BB70 | ProtoLitPass::DrawParts | EQUIVALENT (one instruction: a constant store is scheduled before the loop's first load here, after the compare in the engine) |
| 0x10768670 | ViewPass::Render | EQUIVALENT (6 instructions: the engine loads the device pointer before the colour conversion and keeps the result in eax) |
| 0x10766170 | ProtoOpaquePass::SortParts | EQUIVALENT (the key and scratch arrays sit in the other order in the frame; the last loop reloads the list) |
| 0x10767B60 | ProtoShadowPass::DrawShadowCasters | EQUIVALENT (stack slots of the spilled locals, the loop counters) |
| 0x107654E0 | ProtoDecalPass::Render | EQUIVALENT (registers and the frame; every call, store and float operation is in the engine's order) |
| 0x1076CD90 | ProtoLitPass::SetupLights | EQUIVALENT (stack layout of the four light lists and the scheduling of the constant stores) |

Every EQUIVALENT body makes the same calls with the same arguments in the same order as the engine's (compared
through the call sequence of both) and has the same float operations (same counts of every x87 and SSE instruction);
the sums of squares that /fp:fast reassociates are pinned to the engine's order.

Matching notes:

- `container::ArrayFixed<T, N>` (storage as an `int` array, then the end pointer) is the engine's fixed-capacity array;
  `~PassEntries` only matches (`lea eax, [ecx + 4]; mov [eax + 0x80], eax`) with the storage declared that way. The
  copy constructor is the loop written out (the engine does not call the kept `ConstructCopiesN`), the assignment
  caches the source's end pointer and calls `ConstructCopiesN` for the tail.
- A member defined in the class body is inlined where the compiler likes: the lit pass's list appends came out as
  calls at exactly two sites only once the shader-constant accessor was `__forceinline` (the inline budget of the
  function); the sites that check the fullness first (`if (list.Size() != 8) list.PushBack(light)`) are the calls.
- A pass writes a constant through one inline accessor (`GetConstant(slot, group)`): the slot has to be passed by
  reference (`const int&`) so that its load stays after the `constantsDirty` update, and the accessor takes the table
  pointer into a local between the two.
- The draw parameters are a 12-byte bit-field struct (`PrimStreamParameters`): its constructor assigns blendMode 1,
  blendFactor 0, the 4-bit and 10-bit groups at bits 10 and 14 and three 1-bit flags in the third word. The compiler
  folds consecutive bit-field stores into one `and` / `or` pair, so the engine's three pairs in the decal pass come
  from statement order (blend, bits 14 - 23, the flags, then bits 10 - 13); setting `flag0` and `flag2` as two
  1-bit fields gives `and cl, 0xF8; or cl, 5`, one 3-bit field gives `and cl, 0xFD; or cl, 5`.
- `bool` functions returning a pointer test: `if (p) return true; return false;` gives `setne al`, `return p != 0;`
  gives the longer `xor ecx, ecx; setne cl; mov al, cl`.
- Float to `unsigned int` conversion in a call argument is the inline `fnstcw` / `fistp qword` sequence.
- `core::BitField<T>::Test` has to be `T mask = 1; mask <<= bit; return (mask & mBits) != 0;` for the 16-bit copy
  (`and dx, [eax]`) and the 32-bit one at once.
- A float that comes back from a call is consumed by x87 instructions when it is multiplied in an expression; the
  engine's SSE form (`fstp [tmp]; movss xmm4, [tmp]; mulss ...`) comes from passing the products through an inline
  function that builds a `math::Vector4` (`Scaled(colour, scale)`) and adding its members to the sum. Without it the
  last bit of the light colours would differ (x87 keeps 64 bits between the multiplication and the addition).
- With /fp:fast the order of a sum of three squares follows the order in which the three differences were defined,
  last defined first: `float dy = ...; float dz = ...; float dx = ...; dx * dx + dz * dz + dy * dy` adds x, z, y. A sum
  that stays in x87 registers keeps the left-to-right order of partial-sum statements.
- Caching a loop's end pointer in a local (`for (it = list->begin, end = list->end; it != end; it++)`) is what puts
  the end in a register where the engine has it; leaving `list->end` in the condition re-reads it each time.
- A stack variable that is never initialised on one path (the decal pass's bounding sphere radius when a part has no
  state) keeps the previous part's value in the engine; the reconstruction keeps the same hole.

## ravenphysics (the physics library, 0x10650000 - 0x106DB000): stack allocator, broad / narrow phase glue

37 functions were looked at (`local` pseudocode of each), 18 match, 1 is EQUIVALENT and 6 have their reconstructed body
in the tree under `#ifdef NONMATCHING`. Sources: `src/code/ravenphysics/common/` (StackAllocator, a pointer hash
table), `broadphase/` (the sweep-and-prune sort chain, endpoints, the quantising grid), `collision/` (collision
objects, volumes, collision info, the narrow-phase dispatch, GJK, clipping, the tree query), `batch/` (the mid-phase
pair batch, the narrow-phase batcher's job and pair records) and `src/physicsobject.cpp`. Shared headers touched:
`code/math/obb.h` + `obb.cpp` (`OBB::operator=`, the component-wise copy at 0x100F7120) and the new
`code/core/interlocked.h`.

| Address | Function (names are guesses) | Status |
|---|---|---|
| 0x10686160 | StackAllocatorScope::~StackAllocatorScope (also the ctor 0x10686140, Mark / Release / Init / ctor of the allocator) | match |
| 0x10691BD0 | PairBatch::Begin | match |
| 0x106BA4A0 | std::sort<SortEntry*> (and the eight functions of its chain: _Sort, _Unguarded_partition, _Insertion_sort1, _Make_heap, _Sort_heap, _Median, _Med3, _Adjust_heap) | match |
| 0x106A3EE0, 0x106D8790, 0x106D87C0 | StackAllocator::AllocArray<unsigned short / float / Vector> | match |
| 0x106B2110 | CollideVolumes (7 x 7 dispatch on the volumes' type bytes) | match |
| 0x106B2150 | CollideVolumesSwapped | EQUIVALENT: the original widens both type bytes late (`mov al, [ecx]` ... `movzx eax, al`) and keeps the index in edi |
| 0x10668D10 | CollisionInfo::GetMaterial (and GetFace, 0x10668C60) | match |
| 0x10686570 | PointerHashTable::Find (bucket index truncated to 16 bits before the lookup) | match |
| 0x10662F50 | BroadPhaseGrid::Quantize (16-bit grid cell of a point; `!(v >= 0.0f)` gives the original's `comiss v, 0`) | match |
| 0x106736F0 | GjkSimplex::AddVertex (returns int; the vertex is a `Vector` passed by value) | match |
| 0x100F7120 | OBB::operator= | match |
| 0x10690100 | PairDetails::Set (a method, not a constructor: no `mov eax, ecx`) | match |
| 0x106608A0, 0x106612C0 | PhysicsObject::UpdateBounds / RefreshBounds | match |
| 0x10691C30 | MidPhaseBatcher::Finish | match |
| 0x10690A50 | NarrowPhaseJob::Submit | match |
| 0x106A4BC0 | CollidePair | match |
| 0x10690F70 | NarrowPhaseJob::AddPair | NONMATCHING: late `push ebx / ebp / esi` after the switch and `this` kept on the stack |
| 0x106C0140 | ClipEdges | NONMATCHING: late register saves; edges walked with two induction pointers (edge, edge + 0x14) |
| 0x106C1320 | BuildClipLists | NONMATCHING: late saves; loop pointers biased to the middle of the element |
| 0x106D9260 | BuildEndpoints | NONMATCHING: index in ebp, loop pointers in esi / edi with copies in eax / ecx |
| 0x10677180 | GjkDistance | NONMATCHING: ours merges the first support points' stores with the copies of the closest points |
| 0x106A7750 | QueryTree (compressed tree walk) | NONMATCHING: eight stack-slot locals in the original |
| 0x106D90F0 | SortEndpoints (radix sort of an endpoint list, then the overlap counts) | not done: static with the allocator in eax (called twice from 0x106D9400) |
| 0x106BF5F0, 0x106DAF50 | the contact solver's per-record loop and its SIMD step | not done: the callee takes two `__m128` in xmm0 / xmm1 and six stack words; the caller loops over 36-byte records |
| 0x106D0B80, 0x106D0E90 | corner copy and a contact-add wrapper with debug prints | not done: they call static helpers with eax / ecx / edi arguments (0x106D08B0) |
| 0x106BA4E0 | BroadPhaseDetectorSingleAxisSweepAndPrune::vf22 (the sweep over three sorted endpoint lists) | not done |
| 0x106D9400, 0x106D8890, 0x106BEC40, 0x106D2F90, 0x106A2630, 0x10673750 | large SIMD / pointer-heavy functions (the biggest, 14880 bytes, is the GJK simplex solver) | not done |

What the code shows about the library:

- Static functions with register conventions (the allocator in eax, a list in ecx, `__m128` in xmm0 / xmm1) and
  prologues that push callee-saved registers in the middle of the function are link-time code generation (`/GL`)
  output; per-unit compilation cannot reproduce them (see also enginememory.cpp above). That is what stops AddPair,
  ClipEdges, BuildClipLists and the 0x106D... group; the functions that match have an ordinary prologue.
- The library has two stack allocators: `StackAllocator` instances over a caller buffer (0x10686040 ...) and one
  global scratch stack with its state in globals (0x1127D408 on, `!sLock` asserts, `ScratchStack::Alloc` 0x10666FE0
  whose `this` is a dummy empty object; the statics' pointer names end in `2PADA` (with `2PAD` they mapped nothing
  and our functions kept private copies: the engine's Alloc then crashed the game), `ScratchStackFrame` for the mark / release).
- The narrow-phase job (`NarrowPhaseJob`, 0x134 bytes) is a snapshot of the batcher's queues: six batch pointers, the
  batch pool, a spin lock, the batch slots (0x60 bytes each behind a counter), a copy of each type's `AsyncTask` and
  the profiling log; `Submit` queues a batch with `core::SubmitAsyncTasks`. `PairDetails` is `__declspec(align(16))`
  (sizeof 0x40), which is why `CollidePair` has an aligned frame (`and esp, -16`).
- Collision volumes carry their type in the first byte (0 - 6, the dispatch tables 0x110C48D8 / 0x110C49A0 are 7 x 7),
  the byte after it says "swapped", and mesh volumes keep corners / edge pairs / planes in a `ConvexMesh`.

Matching lessons:

- The STL is the toolchain's own: `std::sort` on an 8-byte struct with `operator<` reproduces the whole chain (nine
  functions) once the instances are explicitly instantiated in the unit; give each instance its `// FUNCTION:` line.
- A member template that the engine calls (not inlines) must be defined after the class body, without `inline`.
- `_InterlockedIncrement(p) - 1` gives `lock xadd; inc; sub 1`, `_InterlockedDecrement(p)` gives `lock xadd -1; dec`,
  `_InterlockedAnd(p, -1)` the compare-exchange loop of an atomic read, `_InterlockedCompareExchange(p, 1, 0)` the spin
  lock. A value that the original reads before it pushes a call's arguments needs a comma expression or a local
  (`if (flag && (n = _InterlockedAnd(p, -1), Report(..., n, 0)) == 3)`); a pointer the original reads late has to be
  loaded inside the condition too.
- Writing the end of a struct through `Vector::Set(x, y, z)` (arguments evaluated first) keeps the following loads
  after the stores as in the original; component-wise stores let the compiler hoist them.
- A one-bit flag read-and-cleared by an inline helper must be a bit-field member (`unsigned char changed : 1`) for
  the `mov cl, al; and cl, 1; and al, 0FEh` form.
- `static bool` report flags that sit next to a call are the pattern of `core::Report(0, " Pre ", file, line, 0,
  format, ...) == 3`; with an assert (`OLD_ASSERT_TEXT_AT`) the expression text is passed and the format is null.
- Two copies of the same call with different argument sources (the pair details built from the objects or from
  stack copies of their ids) must be written as two calls; the compiler shares only the last pushes.
- `if (a != 0 || b != 0) swapped else normal` compiled to the wrong block order; a local
  `bool normalPair = x->swapped == 0 && y->swapped == 0; if (!normalPair) ...` gives the original's.
- Dispatch on a byte with explicit `case 5: return; case 6: return; default: return;` keeps the jump table at 0 - 6
  (identical case bodies are merged into the default otherwise and the table shrinks to the used range).

## fight/effecttrack.cpp (0x10804EC0 - 0x108078E0): open, 127 of 292 functions match, 4 NONMATCHING

The effect track of the fight tree, the actions that carry it and the effect it plays. The unit runs from the thunk
of `LuaScriptManager::CancelAllScheduled` (0x10804ED0) to the first property setter of the track factory
(0x108078E0) and has no assert path; `src/code/engine/fight/effecttrack.{h,cpp}` is named after the RTTI classes it
belongs to. Reconstructed:

- 78 accessors, all matching: 63 on the track (RTTI `engine::EffectTrack` / `AbortEffectTrack` / `MotionTrailTrack`;
  guessed owner) and 15 on the particle effect an action plays (RTTI `engine::Effect`). The track's begin at
  0x108060F0 switches on its member at 0x1A4, so that word, the two Vectors at 0x6C / 0x78, the 36 floats at
  0x88 - 0x114 (nine four-float colours) and the flag bytes at 0x1A8 - 0x1AD are read straight off the engine's
  accessors; the effect's layout (six handles from 0x10, nine Vectors from 0x50, the counter at 0xC8 and the flag at
  0xD0) comes from 0x10805D30 and the action read at +0x1C of the action object.
- 6 free functions around the game's hook on an effect track (0x108056E0 - 0x10805740) and their four globals.
- This unit's own copies of `core::RefAssign` (0x108058E0) and `core::SafeRelease` (0x10805910), written against
  `core::IRefCount` (`AddRef` slot 0, `Release` slot 1).
- The three action classes the tracks drive (RTTI `engine::EffectAction` / `AbortEffectAction` / `MotionTrailAction`,
  nine vtable slots each from `fight::Action`): 0x10807550 / 0x108075F0 / 0x10807700 and their destructors at
  0x10805B10 / 0x10805B40 / 0x10805CF0, plus the three compiler-made scalar deleting destructors at 0x108075A0 /
  0x10807690 / 0x10807770 (no annotation, `symbols.txt` only). An action carries a 12-byte `core::Link<EffectTrack>`
  at +0x1C that inserts itself into the head the track keeps at +8 of itself, and `EffectAction` / `MotionTrailAction`
  a 12-byte `engine::TrackWatch` at +0x28 that registers itself through `fight::Track::Register` / `Unregister` (the
  track's second list at +0x24). The layout the constructors fix: `EffectAction` 0x50 (mode at +0x34, -1 at +0x38,
  a reference at +0x3C and one at +0x44, 0xFFFF at +0x48, a flag at +0x4C), `AbortEffectAction` 0x28,
  `MotionTrailAction` 0x3C. All four action classes are created with the flag word 0xE00.
- `fight::Action` in `sequencer.h` now declares the two out-of-line members of that unit it needs,
  `Action(int flags)` (0x105A23E0) and `virtual ~Action()` (0x105A2530), and `fight::Track::Register` (0x105A3A40);
  the three are new `symbols.txt` entries.
- `core::LinkList<T>` / `core::Link<T>` in the new `src/code/core/linklist.h`: the watch list the engine keeps on an
  object, removed out of line by `core::LinkList<engine::EffectTrack>::Remove` (0x10095300, a kept copy shared with
  the rest of the engine and the only new symbol outside the fight module).

| Function | Status | Why |
|---|---|---|
| 0x10804EE0 EffectTrack::GetUnknown14 | NONMATCHING | the engine loads the member into ecx and the out pointer into eax; ours the other way round (75 %) |
| 0x10805B40 EffectAction::~EffectAction | NONMATCHING | the bytes match, but the +0x3C member is released through 0x104FF200 (another unit's copy of the release helper) where ours calls ReleaseEffectRef twice; caught by objcmp's target check |
| 0x108075F0 EffectAction::EffectAction | NONMATCHING | the engine stores the -1 into the member at +0x38 between the other member stores, ours sinks it past the argument setup of the trailing `AssignEffectRef` call (92.6 %); the statement order and a member-init list both give the same |
| 0x10807700 MotionTrailAction::MotionTrailAction | NONMATCHING | the engine stores the -1 into the member at +0x34 before the parameter store, ours puts the parameter store right after its load and sinks the -1 into the epilogue (90.8 %) |
| 0x10805750 EffectSpawnTransform::BuildMatrix | NONMATCHING | register allocation and scheduling of the head: the engine keeps the 1.0f constant in xmm3 from the first instruction (it is also the static's y component) and loads the direction's components z, x, y where ours loads x, z, y and reloads 1.0f twice; the tail from the comparison on is the engine's (23.6 %) |

The second run of accessors (0x108052D0 - 0x10805540, 39 functions) is reconstructed too: `GetUnknown60` and the floats at 0x118 - 0x17C and 0xA4 - 0xBC, `GetUnknown84`, the second `GetUnknown40` and `GetUnknown1ac`, plus `Effect::GetD1` / `GetHandle48`. **Eight of them repeat an offset the first run already has an accessor for** (0xA4 - 0xBC and 0x40), which one class cannot do: RTTI gives the three track classes the *same* base (`fight::Track`, not `EffectTrack`), so they are siblings that declare their own copies of the members, and this run is written on `MotionTrailTrack`. Which of the two siblings owns it is a guess; the offsets fit both.

### What the next agent needs to know (2026-10-15, ds-4)

- **`engine::Effect`'s layout is now readable off the begin's callers.** `link.object` of an `EffectAction` /
  `AbortEffectAction` is an `EffectTrack` (its +0x1a8 / +0x110 / +0x1a4 are read through it), but the object
  `MotionTrailAction` links to (also at +0x1C) is an **`engine::Effect`**: 0x10805D30 reads +0x50..+0x94 as six
  `math::Vector`s, +0x98..+0xa0 as a seventh, +0xa4..+0xbc as seven single floats, +0xc8 as a value and +0xd0 /
  +0xd1 as two bools. So `Effect` is `{ 8 x core::Name (8 bytes) at 0x10, 7 x math::Vector at 0x50, 7 floats at
  0xa4, float 0xc0, float 0xc4, int 0xc8, float 0xcc, bool 0xd0, bool 0xd1 }` - the "handles" the earlier pass called
  `GetHandle10` .. `GetHandle48` are `core::Name`s and the singles at 0xa4 - 0xbc belong to `Effect`, not to a track.
  The second accessor run (0x108052D0 - 0x10805520) is written on `MotionTrailTrack` as a guess; the owner is still
  open.
- **`EffectAction::Slot5` (0x108076B0)** is `if (link.object == 0) return false; if (gEffectSuspendCount != 0)
  return BeginEffect(link, unknown40, &unknown38, &watch, unknown34, &unknown3c, unknown44, this); unknown4c = true;
  return true;` - the begin (0x108060F0) is a **free function (cdecl)** taking the 12-byte `core::Link` **by value**
  (built in place through 0x10805B90) plus seven dwords, and `link.object` reaches it as the Link's first word.
  `EffectAction::Slot6` (0x10805CA0) and `MotionTrailAction::Slot6` (0x10805FF0) go through the global at
  **0x1130CCE0** (`GetManager`, the getter is 0x108193A0) with **0x1081B730(handle, float)** and
  **0x10819560(Drawable*)**; the second is `if (manager && effect && effect->unknownd0) manager->ReleaseDrawable(&unknown34)`
  and tells that a `MotionTrailAction`'s +0x34 holds the **4-byte `engine::render::Drawable`** the begin produced.
  `MotionTrailAction::Slot5` (0x10805D30, 696 bytes) copies six `Name`s and six `Vector`s out of the Effect, resolves
  the `GameObjectHandle` at the action's +0x38 through gMasterTable (0x1128348C), reads two attributes off it
  (0x112834C8 / 0x112834D0, `FindAttribute`, 0x107E0C00) and calls **0x1081BA90** (`this` = the manager, `ret 0x4C`,
  76 bytes of arguments: the flag pointer, the Drawable, the first attribute's word, a 12-byte and a 28-byte by-value
  block and five pointers/values).
- `AbortEffectAction::Slot5` (0x108075C0) `return false` after
  `manager->0x1081E260(&track->unknown10, track->unknown24, track->unknown18.x)`, so **`EffectTrack`'s +0x10 is a
  `core::Name`** (8 bytes), not an `int`: the accessors `GetUnknown10` / `GetUnknown14` read its two halves.
- Every setter of the track classes is a `bool (__thiscall T::*)(value)` returning true (`mov al, 1; ret 4`), which is
  what the property objects store as their accessor.

Not done (about 160 of the 298 functions of the range):

- **`fight::RefCounted`'s `AddRef` (0x105A73E0) / `Release` (0x105A73F0) and `fight::Action`'s own slots 3
  (0x105A2430 `GetChild`), 4 (0x105A2460 `Slot4(int, float)`) and 8 (0x105A24A0 `Slot8(Action*, int, float)`, which
  copies the flags and the three times) are reconstructed and match** - six of them are in `sequencer.cpp`, which
  makes the three action vtables that far correct (`tools/vtcheck.py` compares every slot it can map). Slots 6
  (0x105A2480) and 7 (0x105A2490) are *declared pure* and defined in `sequencer.cpp` only for their bytes: slot 6 and
  slot 7 are overridden per class (EffectAction 0x10805CA0 / 0x10805BD0, MotionTrailAction 0x10805FF0), and until
  those bodies are written the classes stay abstract, which keeps their vtables dead data (`??_7EffectAction@engine@@6B@`
  and its two siblings are deliberately **not** in `symbols.txt`; the engine's own tables stay). Never map an action
  vtable before its class's overrides are all in place - `ninja dll` would install a table with `_purecall` slots.
- **The three action classes are abstract in our tree and the engine's are not.** The engine's vftables read
  (the dwords at the address `rtti.tsv` gives, the COL pointer right before and the next table right after confirm
  the nine slots) are:

  | slot | `engine::EffectAction` (0x10E6B264) | `AbortEffectAction` (0x10E6B23C) | `MotionTrailAction` (0x10E6B28C) |
  |---|---|---|---|
  | 0 AddRef | 0x105A73E0 | 0x105A73E0 | 0x105A73E0 |
  | 1 Release | 0x105A73F0 | 0x105A73F0 | 0x105A73F0 |
  | 2 destructor | 0x10807690 (`??_G`) | 0x108075A0 (`??_G`) | 0x10807770 (`??_G`) |
  | 3 | 0x105A2430 | 0x105A2430 | 0x105A2430 |
  | 4 | 0x105A2460 | 0x105A2460 | 0x105A2460 |
  | 5 | 0x108076B0 | 0x108075C0 | 0x10805D30 |
  | 6 | 0x10805CA0 | 0x105A2480 | 0x10805FF0 |
  | 7 | 0x10805BD0 | 0x105A2490 | 0x105A2490 |
  | 8 | 0x105A24A0 | 0x105A24A0 | 0x105A24A0 |

  The destructor slot holds the *scalar deleting destructor* — the compiler puts `??_G` there, so `??1EffectAction`
  (0x10805B40) is only ever called from it and the match of 0x10807690 confirms it. The engine's `fight::Action`
  therefore has six non-pure virtuals beyond `AddRef` / `Release` / the destructor, and `fight::RefCounted`
  implements `AddRef` (0x105A73E0, `add [ecx+4], 1; ret`), `Release` (0x105A73F0, the 0x8000000 park) and the
  destructor (0x105A73D0, stores the `fight::RefCounted` vftable 0x10D96DB8 and returns — the 7-byte
  `??1RefCounted@fight@@UAE@XZ` this unit already emits is byte-identical to it). Action's own slots:
  3 = 0x105A2430 (`xor eax,eax; ret`), 4 = 0x105A2460 (`mov al,1; ret 8`), 6 = 0x105A2480 (`ret`),
  7 = 0x105A2490 (`mov al,1; ret 8`), 8 = 0x105A24A0 (three arguments, copies +0xC, +0x10, +0x14, +0x18 into the
  argument). Because `sequencer.h` declares those six pure and `fight::RefCounted` inherits `core::IRefCount`'s pure
  `AddRef` / `Release`, today the three action classes are abstract: our constructors compile and match, but
  `new EffectAction(...)` and the vtables do not. Declaring the six virtuals on `Action` (in the vtable order above,
  with those signatures) and `AddRef` / `Release` / `~RefCounted` on `RefCounted`, with the seven addresses above as
  `symbols.txt` entries, makes the three classes concrete; `vtcheck` then checks every slot. Only then can
  0x10807790 / 0x10807860 / 0x108078A0 (the three functions that make an action — they call the constructors and
  `engine::FindGameObject`, and 0x107FC7A0, an out-of-line `HandleBase` from an object that the first of them
  inlines) and the six slot bodies 0x108075C0 / 0x108076B0 / 0x10805CA0 / 0x10805BD0 / 0x10805D30 (696 bytes) /
  0x10805FF0 be written.
- 0x108058A0 - 0x10805B00 and 0x10806020 - 0x108060B0: 21 kept template copies with no owner in this unit — the
  engine's 12-byte intrusive reference (the object, then `next` at +4 and `prev` at +8; the object keeps the head of
  the list at +8 of itself). A copy for one type is `node->object = t; node->next = t->link; if (t->link)
  t->link->prev = node; node->prev = 0; t->link = node;` (55 bytes) and the converting copy from another reference
  reads the source's pointer first (59 bytes); there are also four 16-byte destructors, seven `return p;` getters,
  `operator bool` at 0x108058A0 and three 3-byte getters next to them. Which type each copy belongs to is not in the
  code, only the node layout is, so they are left alone (as the other units did with their unowned kept copies).
  Our `core::Link<EffectTrack>` constructor and destructor are now emitted as COMDATs in this unit and are
  byte-identical to these copies: the constructor to the 55-byte form (0x10805A70 / 0x10805AB0 / 0x10806020 /
  0x10806060 / 0x108060B0) and the destructor to the 16-byte form (0x108059C0 / 0x10805A10 / 0x10805AF0 /
  0x10805CE0). Five constructor copies and four destructor copies are more than this unit has link types, so the
  addresses cannot be told apart and they are kept out of `symbols.txt`. 0x10805980 is the *converting* constructor
  (`mov eax,ecx; mov ecx,[esp+4]; mov edx,[ecx]; ...`, 59 bytes) and there is a fourth address 0x10805930
  (`read four floats from +0x50 into the argument`) that is a member of some other kept type.
- 0x10805750 (325 bytes): reads a world direction at +0x10 / +0x14 / +0x18 and a position at +0x30 / +0x34 / +0x38,
  compares `1 - dot((0,1,0), direction)` with 0.01 (the constant at 0x10E6B234) and either copies the whole matrix
  or builds an identity matrix with the position and a basis from the cross products. The static (0,1,0) lives at
  0x11284B40 with its initialised flag at 0x11284B4C. Both arguments are taken from the stack and `ret 8`, ecx is
  not read: a static member or a free function whose class is not known.
- 0x108060F0 (5153 bytes): the engine's effect begin, called by all three Slot5 bodies with ten arguments (the action
  link, the object handle, the effect's members and the action itself) — the check that lets the game veto a begin,
  the effect creation through 0x1081BA90 and the per-mode setup.
- 0x108078E0 - 0x10809000: the fight track factory (see below). Its first ten functions are understood:
  0x108078E0 `PlaybackTrack`'s float setter (`bool (__thiscall*)(float)`: `movss [ecx+0x20]; mov al,1; ret 4`),
  0x10807920 / 0x10807940 its `Name` setters at +0x18 / +0x10 (`core::Name::operator=`, 0x100278B3),
  0x10807900 the static list getter (`gList[0x11284B50][index]`), 0x10807960 the constructor (base
  `fight::Track` 0x105AA160, vftable 0x10E6B304, two `core::Name`s at +0x10 / +0x18, 0.0f at +0x20, a byte at +0x24),
  0x10807990 its getter, 0x108079A0 a three-byte `fldz` (`return 0.0f`), 0x108079B0 the destructor (vftable then a tail
  jump to 0x105AA180), 0x108079C0 the factory caster's constructor (`mov [ecx], 0x10E6B348`) and 0x108079D0 a
  `__RTDynamicCast` test (`neg` / `sbb` / `neg`). **`fight::Track`'s constructor and destructor (0x105AA160 /
  0x105AA180) are not reconstructed yet** - they are only needed as declarations plus `symbols.txt` entries. A
  `PlaybackTrack` constructor also installs a 16-slot vtable, so the class must have all of its overrides before its
  constructor may go in (see the note on the action vtables above).

## the fight track factory, first pass (0x108078E0 - 0x10807D00): 26 match, 1 NONMATCHING

`src/code/engine/fight/trackfactory.{h,cpp}` (new unit, no assert path; the file name is a guess) holds the fight
tracks the engine registers and the factory machinery they are looked up with. Reconstructed and byte-identical:

- **`fight::Property` and its type classes** (RTTI: fight::Property 7 slots, PropertyTypeFloat / TypeBool /
  TypeString 8, PropertyTypeName 9; another unit's classes, mapped in `symbols.txt`): 0x10 bytes (vftable, a word at
  +4, the `core::Name` at +8), no virtual destructor; slot 0 is the value's type id (PropertyTypeFloat returns 2),
  slot 1 is "nothing attached yet" and slot 6 hands the value read off an object to slot 7, the class's own setter.
  `fight::PropertyFloatConstRange<T>` / `PropertyBool<T>` override slot 1 (`IsNull`, 0x10807A60 / 0x10807AB0) and
  slot 7 (`Set`, 0x10807A40 / 0x10807A90); `fight::PropertyName<T>` overrides slot 8 (0x10807B30). The setter is a
  `bool (T::*)(value)` at +0x10 (the class is 0x18 bytes, the header's three constructors 0x10807A20 / 0x10807A70 /
  0x10807B10 are 0x20).
- **`fight::TrackFactory`** (2 slots, 0x18 bytes: vftable, a word at +4, the name at +8, 0 at +0x10 and the clear
  function at +0x14) and **`TrackFactoryCaster`** (2 slots, the vfptr alone). The per-class templates
  `TrackFactoryTemplate<T>` (0x10807C60 ctor, 0x10807C90 `CreateTrack` = `new T()`) and
  `TrackFactoryCasterTemplate<T>` (0x108079C0 ctor, 0x108079D0 `IsType` = a `dynamic_cast` test, 0x10807CB0
  `CreateFactory` = `new TrackFactoryTemplate<T>(name)`) are in the header; their out-of-line copies are emitted by
  the explicit instantiations at the end of the .cpp and are byte-identical (objcmp on the mangled names: the
  tooling only reads annotations from .cpp files, so these carry `symbols.txt` entries instead).
- **`engine::PlaybackTrack`** (16 slots, 0x28 bytes): 0x108078E0 / 0x108078F0 the "timeBegin" float and the
  "notifyOnPlaybackFinished" bool, 0x10807920 / 0x10807940 the "state" and "specificPlaybackSet" names (at +0x18 and
  +0x10), 0x10807900 slot 0 = the property list (`Property**` at 0x11284B50), 0x10807910 the list's clear function,
  0x10807960 / 0x108079B0 ctor and destructor, 0x10807990 slot 9 (`GetTimeBegin`, reads +0x20) and 0x108079A0 slot 10
  (returns 0.0f), 0x10807A00 the compiler's scalar deleting destructor, 0x10807AC0 / 0x10807AE0 the two functions
  that make its factory (0x105A9E90 `FindTrackFactory` and 0x105A5D10 `TrackRegistry::AddFactory`).
- **`fight::Track`'s own data** is now in the header: the three words the engine's constructor (0x105AA160) clears —
  +4, the watch head at +8 (`core::LinkList<Track>`) and +0xC. `fight::Param` / `Item` / `Track` also declare the
  vftable slots the engine's tables show (0 pure at Param's slot 0 = the property list, 1-6 and 8 implemented by
  Param/Item, the destructor at slot 7, 9-14 from Track and 15 pure), each mapped in `symbols.txt`; 0x105AA1C0 is
  `??_GTrack`.

NONMATCHING:

- 0x10807B50 `PlaybackTrack::RegisterProperties`: every instruction, the array's 0x3fc memset and the four
  `new PropertyX<PlaybackTrack>(name, setter)` match, but the engine's prologue saves esi *before* the guard test
  (`sub esp, 0x400; cmp [gList], 0; push esi; jne end`) where ours schedules the push after the branch, which shifts
  the jump displacements (98.1 %; the four property objects are built into a `Property* [256]` local and passed to
  0x105A8420).

### What the next agent needs to know (2026-10-15, ds-4)

- **`core::Name` is 8-byte aligned in the engine, 4-byte in our tree.** The evidence: `?FindController@Director@...`
  (0x107DE2A0) opens with `and esp, 0xfffffff8` (MSVC's 8-byte realignment for a by-value 8-aligned class
  parameter), `?GetName@Cinematographer@...` reads its name at +8 (`add ecx, 8`), and the engine's property objects
  are 0x18 bytes although their last member sits at +0x10 — four bytes of tail padding only an 8-byte alignment
  gives. Declaring the name `align(8)` makes the engine's property layout come out right (`+0x10` for the setter,
  0x18 for the object) **but breaks the camera unit and others** (`?StartTransition@Director@...` falls to 33.7 %,
  `?GetName@Cinematographer` moves to +0x10), so it is not a change one agent can make: the tree's other units were
  matched with a 4-aligned name and the whole repository has to be re-checked before the alignment is corrected.
  This unit therefore adds a word at +4 in `Property` and `TrackFactory` (the engine never writes it) to place the
  name at +8, which is what the engine's own constructors expect.
- **`core::Link<T>` in `src/code/core/linklist.h`** now reaches the head through
  `reinterpret_cast<LinkList<T>&>(object->watchList)`: `Track` declares `LinkList<Track> watchList` while the nodes
  that watch a track are `Link<DerivedTrack>`, and every node has the same 12-byte layout.
- **The factory machinery's remaining half** is the seven other track classes: `DialogueTrack` (0x34 bytes,
  properties registered by 0x108A86B0 / 0x108A8A50), `SoundTrack`, `SoundBoolValueTrack`, `MixerTrack`,
  `MusicTrack` (0x98, 0x1087AB10 / 0x1087CC10), `ReverbTrack`, `SoundZoneTrack` (0x1087ABD0 / 0x1087D120), each with
  a 9-byte caster constructor (0x10807CF0 / 0x10807DC0 / 0x10807E90 / 0x10807F60 / 0x10808030 / 0x10808100 /
  0x108081D0), a 36-byte `IsType`, a 35-byte `TrackFactoryTemplate` constructor, a 24-byte `CreateTrack` and a
  57-byte `CreateFactory` — all of them the same templates, so each class only needs its own vtable (read from
  `rtti.tsv`) declared and its own track functions (another unit's) mapped. Then the seven 27-byte
  `CreateXTrackFactory(name)` free functions (0x108082A0 - 0x10808360) and the registration at 0x10808380 that
  binds them to "dialogue", "sound", "soundBoolValue", "mixer", "music", "reverb" and "soundZone".
- The vtable addresses of the classes above are in `rtti.tsv` (0x10E6B46C on), and their `??_R0` type descriptors at
  0x111BECF0 on; the 36-byte `IsType` is a `dynamic_cast` against `fight::TrackFactory` (0x10FFE8B8) and the
  per-class `TrackFactoryTemplate` descriptor.

## the engine tracks and the fight track factory (0x108078E0 - 0x10809000 and on): partially done (see above)

The unit starts at 0x108078E0, the first setter of `engine::PlaybackTrack`, not at 0x10807550 (the actions above
belong to it). It holds the engine tracks themselves — `PlaybackTrack` (vftable 0x10E6B304, 16 slots) is built at
0x10807960: it calls the base `fight::Track` constructor at 0x105AA160, constructs two `core::Name`s at +0x10 and
+0x18, a float at +0x20 and a byte at +0x24, so `fight::Track` is 0x10 bytes (the watch head of `sequencer.h`'s
`Action`/`core::Link` at +8 included) and `PlaybackTrack` is 0x28. Its members are the setters 0x108078E0 (float
+0x20), 0x108078F0 (byte +0x24), 0x10807920 (`Name` +0x18), 0x10807940 (`Name` +0x10) and the getter 0x10807990,
plus 0x108079B0 (destructor, sets 0x10E6B304 and tail-jumps to 0x105AA180) and the scalar deleting destructor
0x10807A00 — none of them need the property templates.

The rest is `fight::TrackFactoryTemplate<T>` / `TrackFactoryCasterTemplate<T>` with the property objects of
`PlaybackTrack`, `DialogueTrack`, `SoundTrack`, `SoundBoolValueTrack`, `MixerTrack`, `MusicTrack`, `ReverbTrack`,
`SoundZoneTrack`, `ScenarioStringTrack` and `engine::scenario::LuaTrack`, plus the registration function at
0x10808380 that binds them to "dialogue", "sound", "soundBoolValue", "mixer", "music", "reverb" and "soundZone".
Every one of them registers properties through `fight::Property<T>` subclasses (`PropertyFloatConstRange`,
`PropertyBool`, `PropertyName`, `PropertyNameList`, `PropertyEnumConstList`, `PropertyVector`, `PropertyColour`,
`PropertyIntConstRange`, `PropertyGroup`, `PropertyTrackGroup`, `PropertyScript`). What the built code fixes:

- A property is 0x18 bytes: the base constructor (external: `fight::PropertyTypeFloat` 0x105A8E90,
  `PropertyTypeName` 0x105A96A0, `PropertyTypeBool` 0x105A8C40, `PropertyGroup` 0x105A9E40) takes the property's
  name as a `const char*`, the derived vtable is set after it (`PropertyFloatConstRange<PlaybackTrack>` 0x10E6B354,
  `PropertyBool<PlaybackTrack>` 0x10E6B378, `PropertyName<PlaybackTrack>` 0x10E6B39C) and the accessor — a pointer
  to a `bool (__thiscall T::*)(value)` setter such as 0x108078E0 — is stored at +0x10. So the templates take the
  setter as a constructor argument and the derived constructors are inline (0x10807A20 is the out-of-line
  `PropertyFloatConstRange<PlaybackTrack>(name, setter)`).
- `TrackFactoryTemplate<T>` (2 slots, 9-byte constructor that only sets the vtable) and
  `TrackFactoryCasterTemplate<T>` (2 slots); each has a pair of heap helpers (24 and 57 bytes) and a name test
  (36 bytes) that calls 0x10A88356 with the RTTI type-descriptor string at 0x10FFE8B8 and the global at
  0x111BEBE0 / 0x111BED40.
- The registration function (0x10807B50, 267 bytes) checks the global at 0x11284B50, builds an array of four
  property pointers on the stack and calls 0x105A8420 with it; 0x10807900 / 0x10807910 / 0x108078F0 / 0x10807910
  are the list's accessors (only 0x10807900 / 0x10807920 / 0x10807940 are in `functions.tsv`, 0x108078F0 and
  0x10807910 are missing from it).
- The unit continues past 0x10809000 (the scenario track and its conditions are at 0x10809460 on), so its boundary
  is a guess. Nothing here is reconstructed: the property and factory templates have to be recovered first.

## Open naming conflict (from the fight units)

`0x105A3A40` / `0x105A3A90` are named both `fight::Branch::Register` / `Unregister` (fighttreebehaviour.cpp) and
`fight::Track::Register` / `Unregister` (effecttrack.cpp) in symbols.txt. One function cannot belong to both classes:
the sequencer unit should settle which class owns it (or whether both derive it from a common base) and the other
name should go.

## collision/src/minimalcollisioninfo.cpp (0x10653150 - 0x10654490), started

The unit that is linked just before collision/src/collisionobject.cpp. It carries no assert string of its own, so
the image does not name its source file: the file name is a guess, and the boundary against collisionobject.cpp is
established by the compiler, not by a string. `CollisionObject::UpdateProperties` (0x106559C0) proves the split
exists: while `IntersectionProperties::IntersectionProperties` (0x10653860) was defined in the same unit as it,
MSVC could see through the constructor and kept the local `IntersectionProperties` in registers, and
UpdateProperties came out 133 bytes and 68.4 % instead of 152 bytes and 100 %. With the registry in a unit of its
own, the constructor is an external call again and UpdateProperties matches.

The unit holds the table of collision object handles (0x1127CAC0, 0x10653150 - 0x10653530), the registry of known
intersection properties (0x10653610 - 0x106538D0, its table at 0x1127CAC4) and the CollisionShape flag accessors
and volume destructors (0x10654380 - 0x10654490).

The IntersectionProperties registry is a flat array: `gIntersectionProperties` (0x1127CAC4, pointer) holds
0x10-byte entries of two unknown words and then the `IntersectionProperties` at +8,
`gIntersectionPropertyCount` (0x1127CACC) is the length, and `IntersectionProperties`'s default constructor is the
first entry's properties, or (-1, -1) when the registry is empty. All three globals (and the loader at 0x1127CAD0)
are the engine's - declared, not defined here - and are mapped in symbols.txt.

## collision/src/collisionobject.cpp (0x106544B0 - 0x10655FC0), started

The unit's assert path (`..\..\..\code\ravenphysics\collision\src\collisionobject.cpp`, lines 322 - 1016) names it.
What is reconstructed is `ravenphysics::CollisionObject` and the cross-unit declarations it needs.

The IntersectionProperties registry (0x10653610 - 0x10653860) is a flat array: `gIntersectionProperties`
(0x1127CAC4, pointer) holds 0x10-byte entries of two unknown words and then the `IntersectionProperties` at +8,
`gIntersectionPropertyCount` (0x1127CACC) is the length, and `IntersectionProperties`'s default constructor is the
first entry's properties, or (-1, -1) when the registry is empty. All three globals (and the loader at 0x1127CAD0)
are the engine's - declared, not defined here - and are mapped in symbols.txt.

Done in this unit (all 100 %): `0x10653610` IntersectionProperties::operator==, `0x10653630`
IntersectionPropertiesEntry::GetProperties, `0x106536D0` FindIntersectionProperty, `0x10653720`
GetIntersectionPropertyCount, `0x10653730` GetIntersectionProperty, `0x10653860` IntersectionProperties
constructor, `0x106538D0` ClearIntersectionPropertiesLoader (a call to `core::RefAssign` with the loader at
0x1127CAD0, which itself is 0x10653800 - a header template instance, so not counted), `0x10654380`
CollisionShape::SetFlag3, `0x106543A0` CollisionShape::IsFlag3 and `0x10654410` CollisionShape::SetFlag4.

NONMATCHING in this unit:

- `0x10653250` CollisionObjectTable::Add: the bumped serial, 70.2 %: the engine reads it out of the slot once and
  keeps it in a register for both stores, ours loads it a second time for the handle; naming the value only moves
  the extra load.
- `0x106532B0` CollisionObjectTable::Remove: the serial test, 35.6 %: the engine materialises the second half of
  the `&&` as a bool (`sete dl` / `test dl, dl`), ours branches on the comparison directly. Every other
  instruction, and the `&&`'s short-circuit, is the same.

Still to do in this unit: the container helpers the handle table is built from (0x10653150 - 0x10653240 and
0x10653360 - 0x10653530: a stack of 16-bit indexes over (begin / size / capacity) at +0/+4/+8 with `IsEmpty` /
`Push` / `Pop` / `Top`, two-argument constructors, a `Free`, and one 3-field and two 2-field `Create` / `Free`
pairs, plus `CollisionObjectTable`'s creation 0x10653530 / 0x106534B0 and the free-list fill 0x10653310, which
`functions.tsv` does not list), the meta type statics of `IntersectionPropertiesLoader` and `ColliderTypeNames`
(0x10653640 / 0x10653680 / 0x10653740 / 0x10653780 / 0x106537C0: `content::ClassInfo` and
`content::NameMetaType` locals behind guard bytes at 0x1127CAE0 and on, which need that unit's own copy of the
`content` meta type templates), the two other refcounted pointer wrappers 0x106538B0, 0x106543B0 (a
`MoveTo(position, flag)` that forwards to `MoveTo(position, center, flag)`; the shape's own `MoveTo(Vector, int)`
is 0x10669E60 in another unit, so this one belongs to a class that is not `CollisionShape` as declared here) and
the four deleting destructors 0x10654430 - 0x10654490 (they need the headers' destructors to be defined and a
matched `delete`, which only a matched ~CollisionObject would emit).

## collision/src/collisionobject.cpp (0x106544B0 - 0x10655FC0)

The engine's `CollisionObject` is 0x80 bytes: a `math::Matrix` at 0, its `core::Name` at 0x40, a 4-byte handle
(index / serial) at 0x48, the volume array at 0x50 with its 16-bit count at 0x54, the changed bit at 0x56, a state
word at 0x58 (bit 31 = active, the low bits a per-volume mask), `IntersectionProperties` at 0x5C, then the shape
(0x64), the owning `PhysicsObject` (0x68), the mesh (0x6C) and one word at 0x70 whose meaning is unknown. The shape
is the 0xE0-byte object the broad phase sees (transform vectors at 0x10 / 0x1C / 0x28 / 0x34, an AABB at 0x70, a
bounding sphere centre at 0x9C, flags in byte 0). The last 12 bytes of the object are not touched by any
reconstructed function, which is why 0x74 - 0x80 is still unknown.

NONMATCHING:

- `0x10654790` SetShape: the detector test, 89.6 %: the engine keeps the loaded pointer in a register and tests
  that, ours compares the member against zero.
- `0x10655DA0` GetRadius: the six min/max accumulators stay in xmm6/xmm5/xmm4 and xmm0/xmm1/xmm2 across the loop
  in the engine and the three sizes are computed with SSE; ours spills all six to the stack and finishes in x87,
  7.9 % (the frame is 8 bytes larger).
- `0x10655EA0` ~CollisionObject: the engine emits `test esi, esi` before each of the four destructor calls, ours
  drops it because the volume pointer was just dereferenced for its type byte; 59.6 %.

Done (all 100 %): `0x10655A60` Print, `0x10655AE0` constructor, `0x10655B60` Initialize, `0x10655BE0` Clone,
`0x10655D90` SetName, `0x10655F60` / `0x10655FC0` CreateCollisionObject and `0x106559C0` UpdateProperties (was
64.4 %: it is an indexed `for (i < volumeCount)` loop, not a countdown, and the volume's two filter words are
one sub-struct, so MSVC forms its address once and reuses it for the second field).

Nothing of 0x10656020 - 0x106564C0 is reconstructed: those functions belong to the units after this one (they use
the handle table's slots and the refcount helpers at 0x106560D0 / 0x106560E0) and the last of them, 0x106564E0, is
ravenphysics/src/context.cpp, another agent's unit.

Lessons:

- An empty body left by `#ifdef NONMATCHING` is inlined away at every call site: a function that is a caller's
  only reason for a call has to be matched for the caller to match too.
- A `delete` of a pointer that the code has already dereferenced keeps no null check in our build, while the
  engine has one; the check is only reproduced when the deleted pointer is not provably non-null.
- The engine's `CollisionVolume` is a base of `CollisionVolume3` (also the face list a type 4 volume keeps at
  +0x60), `CollisionVolume4` (the volume plus that list) and `CollisionVolume6`; their destructors are what the
  object's destructor's four `delete`s call.
- A sub-object whose address the code uses twice in a row (the volume's filter pair, the mesh's element array)
  makes MSVC materialise the address (`add eax, 0x1C` / `add eax, 0x28`) even when the value is dead
  afterwards; a plain pair of scalar members is addressed with two displacements instead. Naming a reference to
  the sub-object is what reproduces it.
- `new ConvexMesh()` only calls the engine's `ConvexMesh` constructor when that constructor is declared; with
  only the members declared the compiler writes its own inline one.
- The mesh of a mesh volume is 0x38 bytes and holds an array of 8-byte elements at +0x28 (begin / end /
  capacity); `CollisionObject::Clone` reserves the same count and re-adds every type 6 volume to it.

- The volume types are 7 (the type byte); `CollisionVolume::UpdateBounds(CollisionObject*)` (0x10665690, another
  unit) is the switch that runs the per-type update, and `CollisionObject`'s `SetCapsuleVolume` / `SetSphereVolume`
  call a per-type setter and a per-type update directly (0x10664BA0 / 0x10664C10 and so on, another unit), so those
  two calls take the *concrete* volume - the class the object stores is typed `CollisionVolume*` and the engine
  hands the same pointer to both.
- `changed = true;` and `changed = count > 0;` are both bitfield stores of a `bool` value: `or byte [this+0x56], 1`
  and the `seta` / `xor` / `and` / `xor` sequence. `changed = count != 0;` gives `setne` and does not match.
- A loop that calls a function taking the object itself reloads the volume count every round (the callee may change
  it); naming the volume (`CollisionVolume* volume = volumes[i];`) is what makes both calls use one register.
- `if (x) { } else { }` has to be written with the non-empty branch first when the engine's branch layout puts the
  else arm out of line.
- A null check on a pointer member (`if (shape != 0) shape->flag = value;`) compares the member against zero in our
  build but loads it into a register in the engine; naming the local (`CollisionShape* currentShape = shape;`) is
  what materialises the load (SetFlag4, 0x10655960). The same trick did not fix the detector test of SetShape.
- A search over an array of structs (`gIntersectionProperties[i].properties.unknown0 == that.unknown0 && ...`)
  materialises `&entry.properties` in the engine; naming the reference (`const IntersectionProperties& current =
  gIntersectionProperties[i].properties;`) is what reproduces the `lea ecx, [ebx + 8]` (FindIntersectionProperty).
- A `switch` over the volume type is not the only shape the engine's COMDAT helper copies take: the free-slot
  stack's `Pop` reads `begin[size - 1]` and *then* decrements when the caller inlines it, while the standalone
  copy at 0x10653190 decrements first - the two are separate instantiations, so a container header has to be
  written to match the call site that is being reconstructed, not the standalone copy.

## ravenphysics/src/context.cpp (0x106564E0 - 0x1065A070): 206 functions match, 6 NONMATCHING

The unit's assert path (`..\..\..\code\ravenphysics\src\context.cpp`, lines 0x15C - 0x81A) names it; `ravenphysics::
Context` is its class and the file starts at 0x106564E0 (right after collisionobject.cpp). Layout recovered so far
(every name is a guess): `mWorld` +0x00 (the polymorphic object the context forwards its queries into by vtable slot
0x10 - 0x54), `placement` +0x08 (a position tracker whose methods live in another unit), `registry` +0x0C,
`unknown10` +0x10 (the body `SetSolverIterations` writes at +0x1C / +0x24), `staticObjects` +0x14 and
`movableObjects` +0x1C (the pm_ commands' lists), `collisionBatch` +0x24 (48-byte entries), `constraintBatch` +0x58
(168-byte entries), `queryBatch` +0x8C, `unknownC4` +0xC4 (the broad phase detector the lists point into),
`unknownD8` +0xD8, `detector` +0x108 (whose own +0x24 holds a pointer to itself and to which the `mCollisionDetectorInternal`
asserts belong), `unknown10C` +0x10C.

Matchable patterns worth reusing:

- Every method that touches the library starts with `OLD_ASSERT_AT(CONTEXT_FILE, <line>, !gLock.IsLocked(),
  "!gLock.IsLocked()", "")`; the per-site `static bool` is the `0x110BDBB0 + n` the code tests.
- The forwards into `mWorld` are direct virtual calls: `mWorld->Slot(a, b, c, unknownC4, d)` pushes right to left, so
  the source argument order is the reverse of the push order (`unknownC4` is the second to last).
- The methods of the classes whose members live in other units (`CollisionBatch`, `ConstraintBatch`, `QueryBatch`,
  `PlacementTracker`, `CollisionDetector`) are only declared here; their symbols are mapped in symbols.txt.
- A method that "returns its first argument" is the engine's idiom for the list inserters (`collisionBatch.Add(first,
  second, 4)` then `return first;`): the compiler loads the first argument into esi at the entry and reuses it.
- `Context::ResetObjectWorld` takes its handle **by value** and is a Context method although it never touches `this`
  (the prologue is `lea ecx, [esp + 0x10]` over a `ret 8`); a free function of the same body fails on the `ret`.
- `Context::RefreshObjectList` is the same shape (`ret 4`, `this` unused) - a free function does not compile to it.
- `CollisionDetector::GetObject` and `GetBodyChecked` load the asserted member before the `cmp eax, 3` (the compiler
  hoists it) and end in **two** epilogues; writing the assert as `OLD_ASSERT_AT` and the `return` once reproduces it.

**Second session (85 more functions match, 3 NONMATCHING).** The 0x10656EA0 - 0x10658170 block is reconstructed: the
library's record runs (`Count()` dividing by 0x34 / 0xA8 / 0xC / 0x2C / 4), the two pointer-run families
(`Begin` / `End` / `SetBegin` / `SetEnd` / `Count` / `operator[]` / `PushBack` / `Find`), the interlocked slot pools
(`Acquire` / `Add` / `Reset` / `ReadCounter` / `Init` / `Release`, with 32- and 16-byte strides), `WorkPools` (the two
pools the collision detection takes its work from, with `Init` / `ResetCounters` / `ReleaseAll` / `Slot`),
`ScratchArray` / `ScratchBytes` (the growable arrays over the scratch stack) and the profiler records. Where the
engine's output names no owner - a bare `ret`, a `(begin, end)` pair, a three-word constructor - the function is
written on a stand-in type named after what its accessor computes, and symbols.txt says "(name guess)"; the stand-ins
are grouped in `context.h` under one comment. `ravenphysics::ScratchStack::AllocArray<T>` (the shape
`StackAllocator::AllocArray` already had) was added to `stackallocator.h` for the 40-, 8- and 124-byte instances.

`Context::WakeObject` (0x10657A50) matches. It needs the engine's *second* copy of the object lookup, 0x1065F500,
which is byte-identical to `ObjectHandle::GetObject` at 0x106560A0 and outside this agent's range: it is reconstructed
here as `ObjectHandle::GetObjectSecond` (`symbols.txt` maps it) and the merge should check that no other unit claims
0x1065F500. `Physicsobject.h`'s `RefreshBounds` takes **one byte**, not a word - the wake path calls it with the
result of a comparison and the engine passes that on with `sete al` and a bare `push eax`, without widening; the
declaration and its `symbols.txt` name changed from `QAEXH@Z` to `QAEX_N@Z`.

NONMATCHING in this range:

- `0x10657B60 Context::SleepObject`: register allocation, 97.6 % - the last list end loads the detector's movable
  count into ecx where the engine loads the static count; both counts are then added the other way round, so only the
  two `movzx` differ. `WakeObject`, whose tail is the same code, does load the movable count first, so the order is
  not a property of the expression: both orders of the sum, the unparenthesised chain and a local holding it all
  compile to the movable-first pair here.
- `0x10658480 IndexedSlotSecond::Get`: register allocation, 32 % - the engine reads the slot index before it stores
  the owner and then loads the owner's run through the same register it stored; ours keeps the owner in a second
  register and reloads through it (25 bytes against 28 with a `value` local, 28 against 28 without).
- `0x10657F20 Context::GetIslandTable` (register allocation, 86.6 %) and `0x10657FA0 Context::GetAwakeTable`
  (88.2 %): the two fill a 40-byte snapshot (32 bytes copied whole from `detector + 0x150` / `+0x34`, then the run
  and count from `+0x124` / `+0x128`, resp. `+0x6C` / `+0x70`), and the engine keeps the detector in edx and the
  output pointer in eax where ours swaps the two; the instructions and their order are otherwise the same. A local
  for either of them, a local for the output, `memcpy` instead of the struct copy, and taking the output by
  reference all compile to the same pair.
- `0x10657D70 Context::GetStatistics`: register allocation and scheduling, 42.4 % - the offsets and the arithmetic
  are the engine's (22 words from the two object lists, the three batches' runs and the detector's counters), but it
  interleaves the detector loads with the words between them and takes each pair's maximum with `cmp; jae; mov`
  where ours compiles to `cmp; cmovb`. Writing the statements in the engine's instruction order moves it from
  38.8 % to 42.4 %.
- `0x10658C50 IndexedSlotThird::Get`: register allocation, 57.7 % - the second copy of the same accessor (owner at
  +0, index at +4, the owner's run at +8), and the engine puts the owner in edx and the walk in eax where ours picks
  the other way round; every instruction is otherwise identical. Naming the owner in a local, dropping the local,
  taking the walk by reference and swapping the two statements all compile to the same 26 bytes.

Two systematic findings worth reusing:

- `Add` on the slot pools and on `StatLog` (0x10658080 / 0x106580D0 / 0x10658200) all carry an explicit
  `test eax, eax` before the `je` where the same code written inline in `Add` reuses the `add`'s flags. The engine's
  `Acquire` is **inlined** into them, and it is the inliner's materialised copy of the returned pointer that keeps
  the test: with the acquire logic in a local `inline` helper that `Add` calls, all three match byte for byte.
- `StatLog` is not this unit's class: it lives in `ravenphysics/batch/midphasebatcher.h`, and its `Add` returns one
  byte there too (`unsigned int` was the earlier guess), so the declaration and the `symbols.txt` name changed from
  `QAEI...` to `QAE_N...`. `MidPhaseBatcher::Finish` calls it and ignores the result.
- **`delete[]` needs `#include <new>`**: without it the compiler's implicit `operator delete[]` is the *scalar*
  `??3@YAXPAX@Z` (0x107DEFD0), and a guarded `delete[] p` compiles to a call to it; the engine's code calls
  `??_V@YAXPAX@Z` (0x107DEFE0). `context.cpp` now includes `<new>` for that reason. (`gamedatabase.cpp` and
  `enginememory.h` get the array operator from `code/engine/system/enginememory.h`, which declares it.)
- A "release the run" cleanup stores the end unconditionally and only *then* tests the pointer -
  `mEnd = mBegin; if (mBegin != 0) delete[] mBegin;` - and the engine's compiler schedules the store between the
  `test` and the `je`; writing the store inside the `if` gives the same instructions one byte order off.

**Third session (39 more functions match, 1 NONMATCHING).** What the collision detection block is made of, so far:

- `Context::detector` (+0x108) is a `CollisionDetector` that **derives from `ScratchStackFrame`** (its `this` is the
  frame: 0x106596F0 opens the level, its destructor 0x10658610 closes it last). While the detection runs it holds
  *itself* in `mCollisionDetectorInternal` (+0x24), which is what every assert in the block tests, and the object the
  detection works on in +0x28 (`GetObject`). +0x08 is **the event its gate waits on** (`core::EventInit` 0x1063D320,
  `EventWait`/`EventDestroy` in the destructor) - the earlier `GetBody`/`body` names were wrong and changed to
  `GetEvent`/`GetEventChecked`/`event`. +0x0C is the `NarrowPhaseBatcher` (0x400 bytes, its own assert path is
  narrowphasebatcher.cpp) and +0x10 the `MidPhaseBatcher` (0x80 bytes, midphasebatcher.cpp); +0x14 the scratch
  allocator scope, +0x18 a pointer to the context's profiler pool (Context+0x10C), +0x1C the context, +0x20 the data.
- `Context`+0x0C is a registry whose own six words are the same (run of 16-bit values, count) pairs the hash table
  has, followed by a `PointerHashTable` at +0x18 and its own count at +0x44 (the constructor 0x10658CC0 zeroes
  everything up to and including the table's last member and leaves +0x44 alone).
- `PointerHashTable` (common/hashtable.h): +0x04 / +0x0C / +0x14 are **32-bit** run counts and +0x24 / +0x28 the free
  list's count and the capacity (the header had `bucketCount` 16-bit, which `Find` matched only because its modulo
  truncates; the member is 32-bit and `Find` now spells the truncation out). `Reset` 0x10658AE0 is the library's, but
  the copy the context calls sits in this unit's range: it is written in context.cpp with the address mapped in
  symbols.txt and **without a `// FUNCTION:` line**, because functions.tsv has no entry for it.

Matched in the third session: the nine ownerless runs of 0x10658A90 - 0x10659620 and their cleanup, the two
`ScratchBytesSecond::Reserve` forms, the two statistics-log forwarders, `Context::CastRay` (0x106593A0) and
`Context::QueryObjectShapeHits` (0x10659420, the world's vtable slot 0x44, which the header now types),
`CollisionDetector::Destructor/Destroy/End/Begin`, `Context::BeginCollision`, `ObjectRegistry`'s constructor and
`Reset`, and `PointerHashTable::Reset`.

The detector's destructor (0x10658610) is written and matches. Its record is a `Record32` local, and that local is
what makes the engine align those methods' frames (`push ebp; mov ebp, esp; and esp, -16`), so `Record32` is
`__declspec(align(16))` in the header; the record's fields are `start`, `end`, `unknown8` (-1), `unknownC`,
`unknown10` / `unknown11` (1) and its `kind` (1 Synchronize, 2 Self collisions, 6 Collide Awoken Islands, 7 Waiting
on gate). Its pool `Add` is inlined at that call site in the engine, so the source calls `AcquireSlot32` directly.

The two getters need `BroadPhaseDetector`'s two tables (heads at +0x34 / +0x150, runs and counts at +0x6C / +0x70
and +0x124 / +0x128) and the statistics getter needs the batches' second runs (`CollisionBatch` +0x24/+0x28,
`ConstraintBatch` +0x24/+0x28, `QueryBatch` +0x20/+0x24) and `Context`'s counters at +0xC8, +0xCC, +0xD0, +0xDC,
+0xEC, +0xF0, +0xF4, +0xF8, +0xFC, +0x100; all of those are now declared, with the layouts the accessors imply.

Also matched in the third session: `Context::ClearObjects` (0x10658F00 - it sleeps every object the detector holds
and then empties the detector, the tracker's tables and the registry, the last two through a tail call) and
`EmptyMembers::Twentieth` (0x10658B60, one of the bare `ret`s).

What is still open in the collision detection block, and what it needs:

- `0x106596F0 CollisionDetector::Run` (714 bytes) and `0x10659F70` (255 bytes, the context's "collide" step) both
  build the detection's scratch buffer: `Alloc(0x10000)` from the scratch stack, then a **0x30-byte local** whose
  constructor stores a byte at +0x18, a dword at +0x1C and calls `StackAllocator::Init(buffer, 0x10000, false)` on
  itself (`0x106596F0` allocates one of those with `Alloc(0x30)` for `detector + 0x14`). Its destructor is the
  one-byte empty function at **0x106860E0**, which the allocator unit owns. Who declares that class is the open
  question for those two functions; `NarrowPhaseBatcher`'s and `MidPhaseBatcher`'s constructors (0x10658F90 /
  0x10659030) are COMDATs of inline constructors those two units' headers define, and `Run` needs them inlined.
  A class that *contains* a `StackAllocator` cannot be written as it stands: our `StackAllocator` declares only its
  three-argument constructor (`??0StackAllocator@...` at 0x10686040), so a member of it is not default-constructible
  and the constructor body cannot write `allocator.unknown18` and call `allocator.Init` on it. Either the original's
  `StackAllocator` is default-constructible - 0x10686040 has exactly `Init`'s body plus `return this`, so it may be a
  plain method whose constructor name is only the earlier session's guess - or the 0x30-byte class derives from it.
- `0x106586E0`, `0x106588B0`, `0x10658D00`, `0x10659070`, `0x106599C0`, `0x10659D50`: the walks themselves (they
  use the detector's +0x150/+0x34 tables, the registry's island runs and `GetObject()`'s object) - not started.
- `0x10657D00`: takes an object out of the detector (`BroadPhaseDetector::RemoveSecond`, 0x106846F0) and clears
  flag bit 2 of the word at the object's +0x0C (`0x1065E560` clears it and zeroes +0x20); nothing in this unit or
  the tree says what class that object is, whose +0x0C is a flags word rather than the bounds a `PhysicsObject`
  has there.
- `0x10658F90` / `0x10659030` are the two batcher constructors (see above); `0x10658F90` zeroes 35 members of a
  0x400-byte object.

Not annotated, because functions.tsv has no entry for it: **0x10658AE0 `PointerHashTable::Reset`**, written in
context.cpp and mapped in symbols.txt (see above). The merge should keep an eye out for another unit claiming that
address.

Still not done in this range:

- `0x10656570` (`jmp 0x106860E0`, a five-byte forwarder), `0x106860E0` itself (an empty function another unit owns)
  and the one-byte `ret` functions 0x10658360 - 0x106583F0, 0x10658B60: which class each belongs to cannot be told
  from the code (the two other runs of bare `ret`s, 0x10657270 - 0x106572E0 and 0x10657780 - 0x10657820, are written
  on `EmptyMembers`).
- `0x10657D00`, `0x10657D70`, `0x10657F20`, `0x10657FA0`: `Context` methods and one big statistics getter over
  `Context`'s batches and the detector's lists. `0x10657D00` calls 0x106846F0 and 0x1065E560, which nothing has
  named yet; 0x10657F20 / 0x10657FA0 copy 32 bytes from `detector + 0x150` / `+0x34` plus two words from
  `+0x124` / `+0x128` (resp. `+0x6C` / `+0x70`), and `BroadPhaseDetector` declares nothing past `unknown0[0x18]`.
  `0x10657D70` reads nine `(begin, end)` pairs of `Context` between +0x24 and +0xB0 and eleven words between +0xC4
  and +0x100, so it needs a fuller `Context` layout than the one above.
- `0x10658610` - `0x10659F70` (the collision detection itself: 0x10658610, 0x106586E0, 0x106588B0, 0x10658D00,
  0x10659070, `Context::CastRay` 0x106593A0, 0x106596F0, 0x106599C0, 0x10659D50, 0x10659EE0, 0x10659F40, 0x10659F70)
  is not started; 0x106599C0 and 0x10659D50 build the detector and its islands (0x10659F70 registers "Collide Awoken
  Islands" with the profiler). 0x10658610 waits on a `core::EventWait` and adds a "Waiting on gate" record to the
  pool at `this + 0x18`, so the gate and the job classes have to be placed first.

## ravenphysics: the handle table, the registry and the unit before context.cpp (sn-units)

Handle table and containers (`collision/src/minimalcollisioninfo.cpp`): `CollisionObjectTable` is created
(0x10653530) and destroyed (0x106534B0) by free functions that inline the containers it is made of, so
`CollisionSlotStack` (a stack of 16-bit slot indexes), `CollisionHandleEntries` and `CollisionHandleSerials` define
their `Create` / `Free` / constructors `inline` in the .cpp above the callers: an inline function is only emitted when
something compiled references it, so the standalone copies the image keeps (`IsEmpty`, `Clear`, `Pop`, `Top`, the
two-word constructors) stay non-inline and are emitted unreferenced, while the ones a matched caller inlines (`Push`
in `Remove`, the constructors, `Create`, `Free`) are `inline` and referenced. `Remove` matches once the liveness test
is an inline helper written `if (index >= count) return false; return serial == handle.serial;` (an `&&` with the
equality last compiles to a branch, the early return to the engine's `sete` / `test`). `Add` stays NONMATCHING (81 %):
the pop is `begin[size - 1]` and then `size--` here, the bumped serial is read once into a register, and the engine
widens it only for the slot's word. 0x10653310 (the free-list fill) and 0x10653F50 (the default registration) are
not in functions.tsv; their symbols carry the size read from the image.

Registry of intersection properties: `IntersectionPropertiesEntry` is a name and the properties; the default
registration (0x10653F50) builds `IntersectionProperties(-1, -1)` with the two-int constructor, which is why it needs no
call to the default constructor. The global at 0x1127CAD0 is the `ColliderTypeNames` load object (its names are the
run at +8), not the `IntersectionPropertiesLoader`; `ClearIntersectionPropertiesLoader` releases it. `delete[]` of the
entry array emits the vector deleting destructor (0x10653AC0, matched, unannotated). EQUIVALENT: the two lookups by
name (the engine loads the array pointer behind the count test) and `RegisterIntersectionProperties` (register
allocation).

Not done in 0x10653640 - 0x10654140: the reflection of `IntersectionPropertiesLoader` and `ColliderTypeNames` (class
infos, name / array meta types, `GetMembers`), the loader class itself (constructor 0x10654020, destructor 0x10654080,
its slots 0x10653E70 / 0x106536C0 / 0x106538A0, 0x106538B0; its names are two arrays whose instantiations
differ from `ArrayDynamicNew<Name>` by something not recovered: the two member arrays have separate array meta type
instances) and the six `return this` copies 0x106540F0 - 0x10654140 / 0x106540E0 / 0x106560F0 (`xchg` with the value in
eax: a file-local register convention).

`CollisionObject` wrappers: the shape's velocity helpers (`Translate`, `GetVelocityAt`, `AddVelocity`, `AddImpulse`,
`AddAngularVelocity`, `MoveFromTo`, `MoveToCenter`) are asserted forwards; `SetShape` and `SetWorld` call
`BroadPhaseDetector::UpdateCollisionObject` (0x10683510, formerly declared on `PhysicsObject`: its `this` is the
detector at +0x34), which also fixed `SetShape` (now a match). The cross product of the angular velocity with a point
(0x10654260, 0x106542F0, 0x10655880, 0x106557A0) stays NONMATCHING (40 - 68 %): the engine stores the product
straight into the result in y, z, x order and adds the linear velocity from registers.
`CollisionShape::SetVectors` (0x106541C0) treats +0x58 as a `math::SymmetricMatrix` (copied, inverted in place). The
scalar deleting destructors of the volume classes (0x10654430 / 0x10654450 / 0x10654470 / 0x10655B30) are plain
methods named `DestroyAndFree`: these classes have no vftable (the volume's type byte is at +0).

The unit before context.cpp (0x10656020 - 0x106564C0, `src/smallobjects.cpp`): stand-ins named after what the
functions do. `ScratchAllocator : StackAllocator` (0x10656340 / 0x10656570, the base's empty destructor is 0x106860E0
and `StackAllocator` has an empty default constructor now), `ProfileTimer`, `AtomicCounter`, `ContextLimits` (the
default constructor stays NONMATCHING, 66 %: the engine stores the third 0x800 behind the float stores),
`CreateObjectHandle` (EQUIVALENT: the output pointer is loaded into eax, ours edx) and small accessors of
`BroadPhaseDetector::ObjectTable`. `ProfileTimer::Start` needed the statement order tag, count, slot, kind, ticks (found
by trying every order).

context.cpp: `NarrowPhaseBatcher` (0x10658F90) and `MidPhaseBatcher` (0x10659030) are the constructors the detector's
`Run` (0x106596F0) calls inline: six `Batch` structures, then pointer words. `Context::CollectBodies` (0x106586E0,
`ret 0x10`: a method that never uses `this`) sorts the bodies of a batch into the static and the movable list; the
engine's list choice is `(mode & 3) == 0 ? static : movable`. Also done: `CollisionDetector::Run` (0x106596F0, the two
batcher constructors inlined, the 0x30-byte scratch class is `ScratchAllocator`), `Context::Destroy` (0x10659D50) and the
`Context` constructor (0x10658D00: 85 stores of zero through one zero register; the `SlotPool` constructor has to be
`inline` so that it folds into it, and the header's batch arrays are named words). `Context::Collide` (0x10659F70) stays
NONMATCHING (95.3 %). Not done: 0x10657D00 (its argument has a flag byte at +0xC that `BroadPhaseObject` does not have:
the argument type is not `PhysicsObject`), 0x106588B0, 0x10659070, 0x106599C0 (the island walks, each 250 - 800 bytes
of inlined containers).

## The start-up, stream, LOD and deform units (2026-10-16, ds-9): 8 match, 0 NONMATCHING, the rest not started

New units, all with guessed file names (none of them has an assert path):

- `code/proto/protomain.cpp` (0x104E02F0 - 0x104E9xxx): the proto game's start-up. `0x104E1ED0`
  (`proto::CreateGameHeaps`) is the game's heap table: 34 `engine::CreateHeap` calls (index, size, extra size, name,
  heap, safety mode, guard, track, flag), the "Name Strings" heap built through a `HeapConfig2` local, and the
  `core::SetStringHeap(0xAF)` under it. Its two command-line switches are `DesyncHunt` / `DesyncHunt2` (their result
  is dropped) and the `BatchMode` / `ExportSchema` / `ExportHelpFile` triple that skips everything but the early
  heaps; `SkipTopLevelMipMap` sets `engine::render::gTextureLoadFlag`. The heap whose name is the bare word "AI"
  (`0xB6`, safety mode 1) is the one the `[0x00004941]` comment in the disassembly hides.
- `code/proto/render/lodrenderbehaviour.cpp`: `proto::LODRenderBehaviour` (RTTI 0x11075320, vftable 0x10DEA9F4,
  8 slots, base `engine::Behaviour`). The class is emitted without its vftable (nothing virtual is declared yet), so
  the offsets are the engine's: +0x3C the fewest levels ever handed over, +0x40 / +0x44 the ready drawables,
  +0x50 / +0x54 the level table (8-byte records), +0x60 the level drawn (-1 in `OnActiveChanged` 0x102DA2C0),
  +0x64 its fade, +0x9C the flags (bit 0 bound, bit 2 forced).
- `code/proto/render/midgroundtexturemanager.cpp`: `proto::MidgroundTextureManager` (RTTI 0x110ACA3C, vftable
  0x10E24538, **one** slot - the destructor). Declaring the destructor out of line is what makes the class the key
  function of this unit, so the vftable, its RTTI and the scalar deleting destructor are emitted here; the engine
  then has 0x105676F0 (destructor), 0x10567670 (`ReleaseScript`) and 0x10567920 (`??_G`).
- `code/engine/system/streammanager.cpp` (0x1082BEC0 - 0x1082E9xx): `engine::StreamManager` itself stays declared in
  `streampackage.h`; this unit holds the collection pass.
- `code/proto/render/deformshaderbehaviour.cpp` (0x102D31B0 - 0x102D50F1): `proto::DeformShaderBehaviour` (vftable
  0x10DEA3CC, base `engine::Behaviour`) keeps the last four dents in a `DentBuffer` (4 dents of 0x20 bytes, then the
  `end` pointer: 0x84 bytes) at +0x10, a bias at +0x94, the live dent count at +0x98, a "changed" byte at +0x9C and a
  "bias message sent" byte at +0x9D. The `DeformShaderModifier` (vtable 0x10DEA3C0, 0x8C bytes, allocated through the
  render event allocator 0x10817A50) carries its own `DentBuffer` at +4 and the bias at +0x88: `AddDent` (0x102D4350)
  is the modifier's. A dent is a `math::Vector`, then five floats - two (target, value) pairs and the time the fade
  has left: {+0x0C target, +0x10 value, +0x14 time, +0x18 target, +0x1C value}.
- `code/engine/system/enginememory.cpp` gained the heap kind name.

Matching notes:

- `engine::HeapConfig2`'s default constructor is inline, so `HeapConfig2 config; config.index = ...;` leaves only the
  fields the assignments do not overwrite at the constructor's own positions: the emitted order is
  extraSize, safetyMode, guard, track, flag (constructor), then index, size, heap, name, alignment (assignments).
- The `math::Clamp` inline emits its `r` through the destination slot; `wanted >= minimumLevels ? wanted :
  minimumLevels` gives the engine's `cmp` / `jb` / `mov` where the equivalent `if` gives a `cmov` (that single change
  took `LODRenderBehaviour::UpdateLevel` from 82 % to 100 %).
- A `(float)` conversion of a value that may be negative is the engine's `fild` / `jns` / `fadd 4294967296.0` pair,
  and a float to `unsigned int` the `fnstcw` / `fldcw` / `fistp qword` one - both in `UpdateLevel`.
- A class whose first out-of-line virtual function is declared but not defined emits neither a vftable nor the
  scalar deleting destructor; defining that destructor (out of line, in its own unit) is what makes MSVC emit both,
  which is how `MidgroundTextureManager`'s `??_G` becomes reachable.

Fixed in the third session (the two findings below):

- `0x107DECD0 GetHeapKindName` matched once it is declared `static`: the heap kind then arrives in eax, as in the
  engine. The six names ("None", "Uncached", "WriteCombine", "Vram", "Vram Preferred", "Vram (heap default)") and
  "Unknown" are the engine's.
- `0x102DA540 LODRenderBehaviour::UpdateFade` matched once the fade is written as two assignments -
  `fade = 1.0f - (clamped - minimum) / (maximum - minimum);` and then `fade = math::Clamp(fade, 0.0f, 1.0f);`. The
  engine's two stores of +0x64 are those two assignments; a single `fade = math::Clamp(1.0f - ..., 0.0f, 1.0f)`
  keeps the pre-clamped value in a register and stores once. The three coordinate differences are a `math::Vector`
  temporary built from the difference expressions: the arguments evaluate right to left, so the engine's z, y, x
  component stores come out in that order.
- `0x1082DB20 AddTriggerPackages` and `0x102D41C0 DentBuffer::Push` matched with the same source as before; Push
  needs `Dent` to carry a user-defined `operator=` that assigns the members one by one (`position.x = dent.position.x;`
  ...), which is what makes the engine's eight `fld` / `fstp` pairs.

Fourth session (2026-10-16, ds-9 continuation):

- `0x102D41C0 DentBuffer::Push` **matches** (100 %). The third session's body was right, the block order was not:
  written as `if (free) { ...; return true; } return false;` (the test inverted, the body inside) the compiler puts
  the `return false` at the tail behind a `je`, as the engine does; with the early `if (full) return false;` it
  inverts the branch and emits `jne` over an in-line `xor al, al; ret`.
- `0x1082DB20 AddTriggerPackages` is at **85.3 %**, not 36 %: the corner loads are not the problem. With
  `float x = min.x + max.x;` (and y, z), `package->unknown4C.x = x * 0.5f;` ... the three sums, the single 0.5f
  and the three products all live in registers exactly as in the engine. What is left is the order: the engine
  evaluates x, y, z with xmm0 / xmm1 / xmm2 and the 0.5f in xmm3 and stores the three products last, ours rotates
  the three register assignments and sinks each store behind its product. A `math::Vector centre` with
  `Add` / `Scale` and an assignment gives the same order as the engine but materialises centre on the stack (the
  assignment goes through memory, 36 %); `package->unknown4C.Add(...); .Scale(0.5f);` is not forwarded (32.7 %);
  the operand order of the sums (`max + min`) makes no difference at all - the front end normalises it.
- `0x102DA540 LODRenderBehaviour::UpdateFade` is at **28.3 %**, not 30 %. The body is the third session's; the wall is
  that the engine computes the three coordinate differences in **SSE** and stores each into the x87 stack slot it
  reads them back from, while this compiler evaluates the whole `dz * dz + dy * dy + dx * dx` on the x87 stack and
  never stores (the frame is 8 bytes instead of 0x14). The three locals (declared z, y, x) reproduce the engine's
  loads, its `add ecx, 4` artifact and its order, so only the SSE/x87 choice is left - the same wall
  `0x102CDFB0 BulletTracerState::GetDistanceFade` hit; it needs a shared answer.
- `0x102DDD30 CellLoaded` / `0x102DDE30 CellUnloaded` are at **86.8 % / 62 %** and are blocked on one fact:
  the engine's `MidgroundCellRecord` is **0x18 bytes** for four members that are 0x14, and its copy leaves the tail
  four bytes alone - the record is eight-byte aligned there because the engine's `core::Name` is (its hash is one
  64-bit word). The tree's `code/core/name.h` declares it as two 32-bit words, so the record is 0x14 and the array
  strides 0x14. Every other byte of both functions is the engine's (verified by putting the alignment back:
  `__declspec(align(8))` on the struct, on the last member, or a union with a `double`, all make the compiler
  realign the frame with `and esp, -8`, which the engine does not have). **`code/core/name.h` is a core header, so
  this session did not touch it: whoever owns it should decide whether `core::Name` carries an 8-byte-aligned
  64-bit hash, which would also shift any other struct that holds one.**
- The class layout `MidgroundManager` needed was the vftable pointer: the engine's class is polymorphic (RTTI base
  `engine::RenderTask::PresentationTask`, vftable 0x10DEAB90) and its constructor 0x102DE380 writes the vftable at
  +0 and a byte 1 at +4, then the scale at +8. Without a virtual member everything after it was 8 bytes off. The
  header now declares a destructor (declared, never defined, so no vftable of ours is emitted) and the base's word.

**`0x1083EC50` `StreamSlotGroup::Create` read in full (fourth session), not written yet - everything below is what it
needs, so the next attempt starts from the source, not from the disassembly.**

Its unit is the cluster 0x1083E760 - 0x1083EC50 (`StreamSlot::Attach` / `Detach` at 0x1083E760 / 0x1083E7A0 are
already named in the header); no source file exists for it yet. The two classes live in `streampackage.h` and are
both undersized there:

- `engine::StreamSlotGroup` is **0x70 bytes** and is polymorphic (its constructor 0x1083EAD0 writes the vftable
  0x10E6F838, and 0x1082D550 `CreateSlotGroup` allocates 0x70 through 0x105FE6C0 and calls its virtual slot 7 with
  (0, 0)). The constructor's writes give the layout: +0x04 a word, +0x08 the `core::Name<core::CaseSensitiveKey>`
  (copy-constructed from the first argument), +0x10 the slot array, +0x14 an int (-1), +0x18 a pointer, +0x1C a byte
  (1, what 0x1083E880 reads), +0x20 the slot count (the constructor's second argument), +0x24 - +0x54 zeroed,
  **+0x5C the slot-heap factory override, +0x60 a word (both written by 0x1082D550), +0x64 the priority
  (0x7FFF, and the constructor's arguments 3 / 4 / 5 are the bytes at +0x66 / +0x67 / +0x68)**. The header's
  `int unknown0[0x64/4]; unsigned short priority;` already puts priority at +0x64, but everything else has to be
  named for `Create` to be writable.
- `engine::StreamSlot` is **0x10 bytes**, not 4: 0x1083E6A0 (the constructor the array's vector-constructor
  iterator calls) writes -1 at +0, a zero at +4, and the three bytes +0xC / +0xD / +0xE as 0 / 1 / 0; +8 is left
  uninitialised and `Create` fills it with the slot's index.
- `Create`'s signature is `void Create(int unused, bool immediate)` (`ret 8`, the first argument is never read).
  Its callees, none of them named yet: `0x1083EC30` = the factory getter (`this->+0x5C`, else
  `engine::gStreamManager->+0x88`, else the default 0x1083EB80), `0x1083E880` = the three config words the factory
  is built from (`out[0] = +0x24 + 1024 * (+0x28 + 1024 * +0x2C)`, `out[1] = the byte at +0x1C`, `out[2] = +0x54`),
  `0x1083EB80` = the default factory (`engine::CreateHeap(handle, config[0], 0, name, 0xC, 2, false, -1, 0)`),
  `0x1082D630` = pops a free slot handle off `engine::gStreamManager->+0xD8` / `+0xDC` (-1 when empty) and
  `0x1082E3F0` = registers the slot in `gStreamManager->+0xE8` under `slot->name.GetHash()`.
  The pieces it is built from are all in the tree: `core::HeapScope` (0x1063AAD0 / 0x1063AAF0),
  `core::GetCurrentHeap` / `SetCurrentHeap`, `container::StringC<64>::Format`, `core::Name::GetText`,
  `engine::CreateTwoWayHeap` (0x107DEB60), `operator new[]` (0x107DEF70) and `new StreamSlot[count]` (MSVC's
  overflow check, the `+4` array cookie and `_vector_constructor_iterator_` at 0x10005100).
  The two-way heap call looks like twelve pushes against a declared eight-argument function, but it is not:
  `CreateTwoWayHeap(heap, count * config[0] + 0x10000, 0, text.buffer, core::GetCurrentHeap(), 2, false, -1)`
  (the declaration in the tree is right - the callee reads exactly those eight, `ret`) and the four constants
  pushed before it (`0`, `&core::IMemoryAllocator::RTTI_Type_Descriptor`, `&core::IMemoryLinearAllocator::
  RTTI_Type_Descriptor`, `0`) are the scheduler setting up `__RTDynamicCast`, which runs after the `add esp, 0x20`.
  Both `Format` calls look like they push the `StringC<64>` object's address as an extra leading argument
  (`lea ecx, [esp+0x28]` then `push ecx`, and `add esp, 0xc` for three arguments). They do not: **MSVC passes a
  variadic member function's `this` as the first *stack* argument, not in `ecx`.** `GameObjectSpawner::Spawn`
  (0x107F2390, 100 % matched) calls the same 0x1060ED50 the same way from the plain source
  `text.Format("gameobject%d", sNameCount++);`, with `ecx` left holding something else entirely. So the two calls
  here are `text.Format("%s StreamSlot", name.GetText());` and
  `text.Format("%s StreamSlot[%d]", name.GetText(), i);` and need nothing special.
  `GetSlotHeapConfig` must be declared **returning `int*`** (`int* GetSlotHeapConfig(int* config)`): the caller
  reads `config[0]` through the call's `eax` with no reload.

0x107DECD0's `?GetHeapKindName@engine@@YAPBDH@Z` symbol in symbols.txt names an internal-linkage function: the
engine's own table entry for it.

Not started (the reason each is blocked, not just "unknown"):

- `0x104E3840` (2354 bytes, `proto::GameEngine` vftable slot 9, the game's start-up) matches: `protomain.cpp`, with the
  seven template instances the unit keeps (the script wrappers of the two natives and `Register<float>`). Its callees
  are named from their own code: 0x104E1440 opens the front end's data file, 0x102E52A0 / 0x10487D10 / 0x105814D0 /
  0x10561A30 / 0x104B55E0 / 0x104BDB70 / 0x104A29E0 make the singletons `ProtoRenderManager`, `SaveGameManager`,
  `UnlockablesManager`, `WebOfIntrigueManager`, `GameFEManager`, `MissionObjectivesManager` and the online manager
  (0x320 bytes; the class is named only by the constructor it jumps to), 0x104E6790 / 0x104DE970 / 0x104E7710 are the
  constructors of `InGameState`, `FrontEndState` and `GamePauseState` (the game keeps them at +4 / +8 / +0xC and the
  simulation driver, `engine::SimulationDriver` 0x10897AC0, at +0x10), 0x10836B40 enters a state in the table of
  states under its number (3 the front end, 2 the game), 0x10836AB0 makes the driver the one the main loop runs,
  0x1082D550 `CreateSlotGroup(name, slotCount, &{size, flag, alignment}, shared, unknown, heap factory, unknown)`
  builds each of the 28 stream slot groups, the Lua natives `util_GetRandomFloat` / `util_GetWorldOrientation` are
  registered between `SetOwner(this)` and `ClearOwner()`, and 0x104E2BC0 / 0x104DDBB0 load the front end packages and
  set the language (`SetLanguage(name, 0)`, the name from `core::GetLanguageName(language)`).
  Matching notes: the 28 `SlotGroupConfig` locals are declared in the order of the calls (that fixes the 0x15C-byte
  frame's offsets); the engine fills them before the first call, and which constants stay in registers there (and so
  the order of the stores) follows the order the source assigns them in - the pair of equal sizes that is finished
  first gets edx. The assignments in `protomain.cpp` are in the order that matches (the call order, with the location
  groups' props and the 7-slot group moved); the last three configs are assigned just before their calls.
  A named group is a block-scope `core::Name<CaseSensitiveKey> name("...", 1)` followed by the call, which puts the
  name constructor in front of the pushes. The report file's flag is `Autotester && !IsDebugLinkClosed()` written as
  one `if`/`else` (the `&&` form compiles to the engine's branches, `autotest = !closed` to `sete`). `SetLanguage`'s
  name needs the language as a local (`int language = LanguageGet();`): nested in the call, the second argument is pushed first.
- `0x1041FA40` (2043, `proto::AmbientManager`'s constructor; the singleton is 0x11267760) is EQUIVALENT (324 of 391
  instructions line up; `ambientmanager.cpp`, with the nine `ArrayDynamicHeap<T>::Allocate` instances the unit keeps,
  which match). The object is 0x618 bytes and the constructor is a long member initialiser list: the 0xA0-byte
  configuration it is given is copied to +0x44; `container::ArrayDynamicHeap` arrays (begin, end, capacity, heap)
  at +0x10, +0x210, +0x220, +0x230, +0x240, +0x250 / +0x260 (0x790-byte elements), +0x520, +0x530 and +0x5A8 are made
  from its counts (heaps 0xA8 and 0xA1; every element size has its own type, as each size has its own `Allocate`
  instance); the fixed pools at +0x270, +0x540, +0x5DC and +0x5EC allocate once with an inline `HeapAllocAligned`
  (end first, then capacity: not `ArrayDynamicHeap`'s order); arrays that are only emptied (+0, +0x20, +0x30 with no
  allocator, +0x5B8 and +0x5CC with the heap stored first) call the copy of the emptying function another unit kept
  (0x1060E6C0, `proto::ArrayStorage::Reset`); eleven 16-byte points start with three float zeros, six of them are
  set again after the script natives are registered (0x1041F210); two 0x8C-byte blocks (constructor 0x104279C0) sit
  at +0xE4 and +0x170; seven `core::Name`s at +0x568. The body makes the parked car cloud manager (0x104 bytes, in
  heap 0xA8) from a 0x60-byte configuration (0x104E7D00 starts it) and creates the three block heaps "PedGameObjectPool"
  (0xA3), "VehGameObjectPool" (0xAA) and "VehiclePhysicsObjectPool" (0xAB); `CreateBlockHeap` takes nine arguments
  (the last is unused). What differs: the schedule of the six points' stores and loads, a few register choices
  and the place of one byte store. `ParkedCarCloudManager` is 0x104 bytes (its `table1C` was far too large).
- `0x1083EC50` (484, the stream slots): it builds a `%s StreamSlot` string, allocates `count * 0x10 + 4` bytes for an
  array of 0x10-byte slots (the element's first word is a per-slot allocator), creates the slots' `CreateTwoWayHeap`
  (0x107DEB60) and dynamic-casts the result; it needs `container::String`, 0x1083EC30, 0x1083E880, 0x1082D630 and
  0x1082E3F0 named first.
- `0x10899830` (454, `engine::StreamDriverBehaviour::update`): read in the third session, it is `Update(float,
  unsigned short)` (ret 8) so it needs that class's vftable like the LOD slots. Its callees are
  `StreamTrigger::Contains` (0x10835480), `StreamTrigger::FindPackage` (0x10835550), `AddTriggerPackages` (0x1082DB20,
  done), `StreamPackage::IsLoaded` (0x107FB040), 0x1082BF40, 0x104B1860, 0x10899770 and 0x1082E100. Its members:
  +0x0C the `TagSet`, +0x34 / +0x38 two package arrays (each a pointer to an array object whose +0 and +4 are the
  begin and end), +0x3C and +0x40 trigger pointers, +0x4C / +0x4D / +0x4E / +0x4F / +0x50 / +0x51 bytes.
- `0x1082E100` (752, the stream transition): four arguments (two package arrays, a `char*` flag and a `bool`), no
  class layout of its own - it works on `int*` pairs - so it is the best candidate of the block that needs no vtable.
  Its callees are 0x1063A8D0 / 0x1063A9C0 (a fixed-block heap alloc and free over heap 0xC, 0x40 bytes, 16-aligned),
  0x1082E050, 0x107FB080, 0x107FB050, 0x1083E950, 0x1083E990, 0x1083E9E0, 0x107FB500, 0x107FB450, the stream manager
  (0x1130D350, its +0x11C is set to 0xFFFF) and 0x1130D388.
- `0x1083EC50` (484, the stream slot group's create): `void Create(int unused, bool immediate)` (ret 8). The object
  is +0x08 a `core::Name`, +0x10 the 0x10-byte slot array (`count * 0x10 + 4` bytes, the first word the count),
  +0x14 the heap, +0x18 the two-way allocator, +0x20 the slot count and +0x66 a byte; the per-slot strings are
  `"%s StreamSlot"` and `"%s StreamSlot[%d]"`. It needs 0x1083EC30 (the factory interface's vtable getter),
  0x1083E6A0 (the slot's placement constructor the vector-constructor iterator at 0x10005100 calls), 0x1083E880,
  0x1082D630 and 0x1082E3F0 named and declared first.
- `0x102D4920` (602, `DeformShaderBehaviour::Update`, vftable slot 4) matches. The class declares `Slot0` first and
  never defines it, so the vftable stays with the engine's copy; the bias message (`SetLODBiasMessage`, vftable
  0x10DEA384, a `ProtoRenderMsg` of type 0x3D with id 2) is built inline, so the unit emits that one-slot vftable. The
  stack message's final destructor store is the base `Message` vftable, which the inline destructors leave. The two
  clamps are `math::Min` written as two assignments (a store, then `Min` of the value and the target), and the bias is
  copied as raw bits (`unsigned int`), where a `float` member is copied through the x87 unit.
- `0x102D4C50` (1097, `DeformShaderModifier::Apply`, the modifier's only virtual) is EQUIVALENT (236 of 284
  instructions line up; the modifier's constructor 0x102D4810, destructor 0x102D4830 and the five atexit stubs of its
  names match, so the unit emits the modifier's vftable). It runs on the render thread for a `DrawableImpl` (a
  `pure3d::Drawable`): five function-local `core::Name<CaseInsensitiveKey32>` statics ("damage_pt1" .. "damage_pt4",
  "crush_params", guard bits at 0x1125E020) and, for every part (0x12C bytes each) that has all four damage inputs
  (`shader->GetSortKey()` answers the shader's input table, whose `Find(4, name)` is 0x106184E0; the helper is a
  `pure3d::ShaderInputs` here) and, for a mesh primitive (type 2), bit 29 of its word at +0x148 (0x10707460), the part's
  binding (made through the inlined `DrawablePart::GetBindingSource` and `PartBindingSource::CreateBinding` when it has
  none): the four dents as `SetVector4(damage_ptN, {x, y, z, value})` and the second values as `crush_params`; with no
  dents all five are set to zero. It destroys itself at the end (`delete this`: 0x102D4830, `FreeRenderEvent`).
  What differs: the engine keeps the binding in ebp and the buffer in ebx, tests the buffer's emptiness with its own
  compare, and has the object and the part number in the other order in the frame. The six `PartRef`s are named
  locals (temporaries put them in other slots), the buffer is reached through `DentBuffer::Size()`, and a `Mesh`
  pointer local makes the part address fold the way the engine's does.
- `0x102DA540` (350, `LODRenderBehaviour`'s per-frame update): the engine leaves a dead `add ecx, 4` in it (the
  game object's address advanced past its handle and then dropped), which no plain `/O2` build of the recovered
  body reproduces.
- `0x102DAF80` (681) and `0x102DC5F0` (557) are `LODRenderBehaviour`'s vftable slots 4 and 1, so they need the whole
  class with its vftable and every slot mapped. **The eight slots are** (declaring the class with Behaviour's eight
  virtuals and running `tools/vtcheck.py` prints them): 0 `Behaviour::Slot0` (0x100610E0, the copy the engine's vftable
  holds - leave the override out and the slot follows the engine's own), 1 `0x102DC5F0`, 2 `Behaviour::Slot2`
  (0x107EE490, likewise not overridden), 3 `0x102DA2C0`, 4 `0x102DAF80`, 5 `0x102D9E80` (60 bytes, an easy one: it
  only reads message type 0x16, id 6 and scales a byte at `message->+0xC` by the level count at `available->+0x18`),
  6 `0x102DC8C0` (a 61-case switch on the message type at `message->+4`, its jump table of seven handlers starts at
  0x102DC9B8 and its byte index table at 0x102DC9D8), 7 the deleting destructor (exempt).
  The class members the slots need: +0x0C a pointer whose +4 is a `pure3d::Pose*`, +0x10 a pointer whose +4 is a
  `math::Vector`, +0x1C / +0x24 and +0x20 / +0x28 `LODLevel*` pointers (`struct LODLevel { render::Drawable drawable;
  unsigned short unknown4; unsigned short unknown6; };` - 0x102D9450 clears the two words and calls
  `Drawable::SetRegistered(false)`, the engine's level records are 8 bytes), +0x2C another `Drawable*`, +0x30 the
  available-levels object with its index at +0x34, +0x38 `distanceLevel`, +0x3C `minimumLevels`, +0x40 / +0x44 the
  ready drawables and +0x50 / +0x54 the level table (0x10- and 8-byte records), +0x60 level, +0x64 fade, +0x68 a
  second fade, +0x6C / +0x70 / +0x74 / +0x78 four floats `OnMessage` sets to 1, +0x90 / +0x94 / +0x98 the level
  object's heap, heap and handle, +0x9C flags. `0x102DAF80` also shows the matrix copy (16 `movss` from
  `owner->transform->value`, `math::Matrix`'s user copy constructor), `Matrix::Scale` on a `Matrix::IDENTITY` copy and
  `matrix.Multiply(scale, matrix)`.
- `0x102DE130` (`proto::MidgroundManager::Load`, 425 bytes): the third session declared the class and matched
  `CellLoaded` (0x102DDD30) and `CellUnloaded` (0x102DDE30) from it; `Load` still needs `engine::GameDatabase::
  GetString` (0x107F8850), 0x104DF9E0, `container::String::Format` (0x1060ED50), 0x108258B0 / 0x108258C0 on the
  inventory's `content::IRefCount`s, `core::HeapScope` (0x1063AAD0), `content::gInventoryLock` (0x11276950) with
  `core::CriticalSectionEnter` / `Leave`, 0x108490A0 / 0x10849540 over 0x1125E2C0, and `__RTDynamicCast` to
  `engine::render::DrawableArchetype`. The manager's layout the two matched functions gave: +0x08 a float,
  +0x0C a `container::ArrayDynamicHeap<render::Drawable>` (its `end` at +0x10 and `capacity` at +0x14 are what
  `Load` walks), +0x1C the 0x28-byte cell index, +0x44 a `container::ArrayDynamicHeap<MidgroundCellRecord>`
  (0x18-byte records: a `core::Name`, a `render::Drawable*`, an int and a float).
  The map is `proto::MidgroundMap` in the unit's header (the third session): +0x00 the capacity (a power of two, the
  mask is it minus one), +0x04 the live count, +0x18 the heap the tables come from, +0x1C the bucket array,
  +0x20 the key array and +0x24 a `render::Drawable` sentinel whose *address* is what an empty bucket holds. The
  key is the 8 bytes `cell->unknown54->name.GetHash()` returns. The iterator is
  `{MidgroundMap* map; int unknown4; unsigned __int64 key; int index; int current; int step;}`, its `step` is
  `((key >> 9) & 0xFE) | 1` and `unknown4` is deliberately left uninitialised by the constructor (the engine's own
  code does not write it). `Find` is the engine's 0x102DD6F0 and the unit also has a second copy of it at 0x102DD7B0
  (the one `Insert` calls), plus `Next` (0x102DD3B0), `Insert` (0x102DDAD0) and `Grow` (0x102DDBA0) - none of those
  is declared in our header yet, only `Find` is, because that is what the two matched functions call.
  The record is `MidgroundCellRecord { core::Name name; render::Drawable* drawable; int unknownC; float unknown10; }`
  in a `container::ArrayDynamicHeap` at +0x44: the drawable member is a *pointer*, and the 0x18-byte stride comes
  from the record's eight-byte alignment (`ArrayDynamicHeap::EraseFast` is what `CellUnloaded` calls).
  The cell is reached through its +0x54, and the `%s_midground` name of `0x102DE130` goes through
  0x1082E010 / 0x108258B0 / 0x108258C0 and the `content::LoadInventory` iterator (0x102D22C0 / 0x102D2830).

Layouts recovered in the second session (all in headers, nothing compiled yet):

- `proto::LODRenderBehaviour` derives from `engine::Behaviour` (0xC bytes), so its own members start at +0x0C:
  +0x0C the pose source (a `pure3d::Pose` at its +4), +0x10 the scale source (a `math::Vector` at its +4),
  +0x1C / +0x24 the level records of the level drawn and +0x20 / +0x28 the ones drawn before it was forced,
  +0x2C the drawable the animation plays on, +0x30 the object the levels come from with the chosen index at +0x34,
  +0x38 the distance range the object is in, +0x3C `minimumLevels`, +0x40 / +0x44 the ready drawables (0x10-byte
  records), +0x50 / +0x54 the level table (8-byte records: a `render::Drawable` and four more bytes),
  +0x60 the level drawn, +0x64 the fade, +0x68 a second fade (0x102D9BF0 advances it by the level's rate × dt),
  +0x6C / +0x70 / +0x74 the fade-in position and its target and scale, +0x78 the behaviour's fade-distance
  multiplier, +0x90 / +0x94 / +0x98 the level object's heap, +0x9C the flags. `UpdateLevel` still matches with the
  real base class. The unit's globals are 0x11075114 (the three distance thresholds), 0x11075120 (a distance
  multiplier, 1.0), 0x1107517C (three 12-byte records: minimum, maximum, rate) and 0x11263108 (the pointer the
  fade asks for the camera's detail scale through, 0x1032C430: `scale / camera->+0x2C`, 1 without one).
- `engine::camera::Camera` has its world position at +0xC0 (a `math::Vector`); `Director::GetCameraUnknown40`
  hands out the word at the camera's +0x40, which the LOD code uses as a camera of its own.

Shared headers touched: `code/engine/system/streampackage.h` (`StreamPackage::unknown4C` is a `math::Vector`, the
centre of the trigger's box the manager writes into it), `code/pure3d/shadows/shadowrendermanager.h` (the class's
layout grew to its real 0x34 bytes, plus the constructor, `Create` and `gShadowMapHeap`) and, in the second session,
`code/engine/camera/camera.h` (the position at +0xC0) and `code/proto/render/lodrenderbehaviour.h` (the base class,
the members above and `LODRange` / `gLODRanges` / `gLODDistanceScale` / `LODDetailScale` / `gLODDetailScale`, four
of whose symbols are in symbols.txt but referenced by nothing yet).

Matching session (op-finish, 2026-10-18):

- 0x10899830 `StreamDriverBehaviour::Update` **matches**: the position with `position.Set(m.m[3][0], m.m[3][1],
  m.m[3][2])` (loads before stores), the two searches as `for (i = n; i != 0;) { i--; trigger = begin[i]; ... }`, and
  `if (found != 0) AddTriggerPackages(...); else wanted->end = wanted->begin;` (the call block at the end).
- 0x102DA540 `LODRenderBehaviour::UpdateFade` **matches**: the fade is reset through a reference (`float& reset = fade;
  reset = 1.0f;`), which keeps the store ahead of the load and compare of the ready range (the same trick matched
  0x10620A20 / 0x10620B00).
- 0x102DC5F0 `Slot1` stays EQUIVALENT (79.4 %): `distanceLevel = 0` after the half diagonal gives the engine's store
  (its zero shared with the loop), but the readiness tests and the joint loop still pick other registers (60 % with
  it).
- 0x102DE130 `MidgroundManager::Load` matches: the package's name is an eight-byte aligned local
  (`__declspec(align(8))`); `core::Name` itself stays four-byte aligned (an eight-byte aligned Name breaks 92
  functions whose classes hold a Name at a 4-mod-8 offset).
- 0x102DDD30 `CellLoaded` stays EQUIVALENT (97.5 %): a reference to the drawable member in the record's copy
  constructor gets ecx right (99.0 %), the 1 still goes to eax for the engine's edx; the union Name above does not
  change it.
- 0x1082DB20 `AddTriggerPackages` stays EQUIVALENT (98.9 %): the x sum's operand order (min first) resists every
  spelling (helpers, references, Set, the eight operand orders, statement orders).
- 0x1082E100 `UpdateStreamTransition` stays EQUIVALENT (21.1 %): the two package sets are 16 bytes and contiguous in
  the engine's frame (`set->begin = HeapAllocAligned(...)` written through the set, a fourth word): ours now are
  too; the arrays and counts are still in other registers. difftest SAME.
- 0x102D4C50 `DeformShaderModifier::Apply` stays EQUIVALENT (69.9 %): the engine tests the dent buffer with
  `IsEmpty()` and re-reads `Size()` in the loop condition (58.9 % with that: the binding and the buffer then swap
  ebp / ebx).
- 0x1041FA40 `AmbientManager::AmbientManager` stays EQUIVALENT (28.9 %, 37 of 396 instruction lines differ, was 95):
  the six points are written through `AmbientPoint& point = ...;` blocks (the config values copied by fld / fstp next
  to their stores, not hoisted), the empty name is a named block local, and the flag at +0x4DC with the point at
  +0x4E0 is one sub-object whose constructor stores the point first (`AmbientTarget`). Left: the engine copies the
  pools' heap into eax / ecx before pushing it.

## pure3d/atg4/platform/win32/skin.cpp (0x1071B000 - 0x10721200), started

The unit's assert path names it (`..\..\..\code\pure3d\atg4\platform\win32\skin.cpp`, lines 0x298 - 0x880, about 2200
lines of source). It is big: 128 functions, about 25 KB, and it holds **pure3d::SkinState**, **pure3d::Skin** and the
task adaptor `pure3d::SkinState::AsyncTaskAdaptor` (the RTTI vftables are 0x10E5BE50 / 0x10E5BE88 / 0x10E5BDC4). The
first session (2026-10-16) placed the SkinState class and matched the small accessors.

**What is known about the two classes** (layouts recovered from the vtable slots and the code):

- `pure3d::SkinState` (0x2E4 bytes, vtable 0x10E5BE88, 11 slots): RefCounted's AddRef / Release at 0 / 1, then
  `~`(2), `Unknown3`(3 = 0x10720C60, makes a 0x350-byte copy of the state through 0x10720A00), `Update`(4 =
  0x10721160), `Unknown5`(5 = 0x1071B0B0), `Unknown6`(6 = 0x1071B0F0), `GetBoundingBox`(7 = 0x1071B130),
  `Unknown8`(8 = 0x1071B240), `Unknown9`(9 = 0x1071F900) and its own slot 10 (0x1071B1C0). Members: a controller at
  +0x70, the expression and its state at +0x74 / +0x78, two pose-sized (0x118-byte) members at +0x7C and +0x194
  built by `FUN_1061B600` and pointed at by `mPoses[2]` at +0x2B0 (index at +0x2C0, the blend index at +0x2B8, the
  frame counter at +0x2BC), the bounding box at +0x2C4 (min) / +0x2D0 (max), the two FrameControllers at +0x2DC /
  +0x2E0. `GetPose` / `GetBlendPose` / `GetPose(int)` index `mPoses` (the last two one element on, which is what the
  original's `[ecx + i*4 + 0x2B4]` addresses are).
- `pure3d::Skin` (vtable 0x10E5BE50, 13 slots): AddRef / Release, `~`(2 = 0x10720200), `Draw`(3 = 0x1071ED50),
  `Unknown4`(4 = 0x10721140), `GetBoundingBox`(5 = 0x1071EF00, copies the box at +0x26C), `GetCentre`(6 =
  0x1071F9D0, copies 16 bytes from +0x284), `FillBatch`(7 = 0x1071EE50), slot 8 (0x1001D6DD, an inherited pure slot),
  +0x294(get / set) at 9 / 10, `SetBoundingBox`(11 = 0x1071EF40) and the 16-byte setter at 12 (0x1071EF80). Own
  members start at +0x1C; +0x70 holds the pose the bone matrices (+0x38) come from; +0x138 / +0x13C / +0x140 /
  +0x144 (a `pure3d::PrimBuffer*`, `Unlock`ed at 0x1071EFE0) / +0x148 (three one-line wrappers at 0x1071ED40 /
  0x1071EFD0 / 0x1071EFF0); an `core::AsyncTaskJob` at +0x20 (0x1071EAE0 submits it).

**The unit's Vector copies go through the x87 stack - solved, see the three ways above; no user-defined operator= is
needed and `math/vector.h` stays as it is.** The first session's measurements still explain why a struct assignment
would not do: they copy each
component with `fld` / `fstp`, in the order (max, min), while our `math::Vector` copies with integer moves. Measured
on 2026-10-16 with scratch functions in skin.cpp: MSVC 2005 gives `fld` / `fstp` for a **user-defined `operator=`**
(`T& operator=(const T& v) { x = v.x; y = v.y; z = v.z; return *this; }` as a member of the 3-float class) and for
the **return-value copy** of a class with a user-defined copy constructor; it gives integer moves for the implicit
assignment of a POD, for an in-place copy construction through a temporary, and `movss` for a user-defined copy
constructor built into a local. A user-defined `operator=` in `math/vector.h` made both functions match but changed
every unit that copies vectors through assignment: it moved one function in `math` from matching to not matching (75
bytes) and one in `engine` the other way, so it is not viable. `math/vector.h` must stay exactly as it is; units whose
vectors are copied member by member depend on the implicit operator.

**The unit's own helpers that are placed.** The three lock-free list helpers at 0x1071B000 / 0x1071B010 / 0x1071B040
(`void**` head, the node's first word is its link) are `StoreListHead` / `PushListHead` / `PopListHead`; `PopListHead`
is `__inline` (0x1071F780 has its body copied in twice, and the standalone copy at 0x1071B040 is the COMDAT one).
0x1071B270 / 0x1071B2C0 are the two four-wide blends returning `__m128` (`a * w.x + b * w.y + c * w.z [+ d]`), with
`const __m128&` arguments (pointers on the stack). 0x1071B080 / 0x1071B1F0 / 0x1071EFC0 are empty one-byte
functions, named `Unknown<address>` because their classes and callers are in other units. The two globals the queue
uses are 0x11281814 (the head of the pending-skin list, a `SkinJobEntry*` whose node is `SkinState::entry` at +0x33C)
and 0x11281828 (the number of running jobs); 0x1071F780 `SubmitPendingSkins` drains the list and 0x1071F7F0
`WaitForSkinJobs` spins on `_InterlockedAnd(&gSkinJobCount, -1) > 0` with `core::ThreadSleep(0)`.

**The classes the second session added to shared headers** (all append-only; `pure3d::Skin` is new):

- `pure3d::Skin` in `src/code/pure3d/primitive.h`: `Primitive` (0x1C) + a pointer at +0x1C, `core::AsyncTaskJob job`
  at +0x20 (72 bytes, so it ends at +0x67), 8 bytes of padding, the pose at +0x70, the `pure3d::PrimBuffer*` at +0x144
  (its stream, still an untyped pointer, at +0x148), the box at +0x26C, a `math::Vector4` centre at +0x284 and a word
  at +0x294 (vtable slots 9 / 10). The class is declared with the 13 known slots but only the non-`Draw` slots are
  defined yet, so MSVC emits no vftable for it here; `Draw`(3), `Unknown4`(4), `GetCentre`(6) and `FillBatch`(7) are
  still unmapped in symbols.txt and have to be added when they are reconstructed.
- `pure3d::SkinState`: `Update`(4 = 0x10721160), `Unknown10720CF0` (0x10720CF0, declared, mapped, not reconstructed),
  `GetUnknown2AC` (0x107211D0), the flag at +0x2AC and the entry at +0x33C. The class is 0x350 bytes (0x10720C60
  allocates 0x350 and 0x10720A00 copies that much), not 0x2E4 as the first session thought.
- `pure3d::SkinState::AsyncTaskAdaptor` (nested, `core::AsyncTaskCallback` + `SkinState* mState` at +4, constructor
  0x1071B090, `OnResult` 0x1071FCC0 = `mState-><0x1071F8A0>` which is mapped in symbols.txt but not reconstructed).
- `pure3d::pddiBaseContext::GetFrameCount` (0x10615180) and `pure3d::PrimBuffer::Unknown10625FA0` (0x10625FA0) were
  added as declarations for the same reason.
- One unused-by-us helper: `SubmitTask` (0x1071EAE0) sits at the top of the Skin layout and is called from
  0x1071F780, so the `job` member has to stay at +0x20.

0x1071B310 / 0x1071B490 are written now (both NONMATCHING, see the end of the section). Remaining, in address
order: 0x1071B310 / 0x1071B490 (the two 4-bone row blends over a 0x40-byte bone record whose
four `unsigned short` indices sit at +0x40 / +0x50; their source is four statement-shaped accumulations -
`out = m0 * w0; out += m1 * w1; ...`, each row of the record transformed by a different bone - so they are
`BlendRows4`/`BlendRows3`-like but written as accumulate-into-memory, and 0x1071F060 shows the same helper family),
0x1071B610 and the long run 0x1071B9A0 - 0x1071E8F0 (the
skinning paths; each ends by writing the box at +0x2C4 / +0x2D0 from stack accumulators and is picked by the
0x350-byte job state's flags at +0x2AE / +0xBF / +0xC5 / +0x1D and the `unsigned` at 0x1071ED50's +0x20000000 bit),
the Skin methods 0x1071ED40 - 0x1071F020 (the +0x148 wrappers, `FillBatch`, `Draw`), the ~100-byte cluster
0x1071F3C0 - 0x1071FCC0 (COMDAT copies of a 6-field ring/table class - +0 valid, +4 pointer, +8 / +0xC / +0x10, +0x14
count - and of `core::SafeRelease<T>` / `core::RefAssign<T>`, whose template arguments still have to be read off the
callers), 0x1071F7D0 (`"AsyncSkinning"` registered with the task callback 0x1071EAF0 through 0x10B80220), 0x1071F840
- 0x1071F880 (the three SkinState setters, which are 0x1071F480 / 0x10707710 / 0x1071F4B0 on +0x78 / +0x2DC /
  +0x2E0), 0x1071F8A0 (the state's job-result handler; its first call is `*(void**)(this + 0x70)` released through
  0x106E2A50, a non-virtual `Release` whose class is still unknown), 0x1071F900 - 0x10721200 (the `GpuSkinState` /
  `GpuSkin` half) and 0x10720200 - 0x10720CF0 (the destructors, the copy constructor and the job dispatcher
  0x10720CF0).

Match so far (42 functions): 0x1071B000, 0x1071B010, 0x1071B040, 0x1071B070, 0x1071B080, 0x1071B090, 0x1071B0B0,
0x1071B0F0, 0x1071B130, 0x1071B170, 0x1071B1B0, 0x1071B1C0, 0x1071B1D0, 0x1071B1E0, 0x1071B1F0, 0x1071B200,
0x1071B210, 0x1071B220, 0x1071B230, 0x1071B240, 0x1071B270, 0x1071B2C0, 0x1071EAE0, 0x1071EF00, 0x1071EF40,
0x1071EF80, 0x1071EFB0, 0x1071EFC0, 0x1071EFE0, 0x1071F000, 0x1071F020, 0x1071F060, 0x1071F180, 0x1071F2A0,
0x1071F780, 0x1071F7F0, 0x1071F880, 0x1071F9B0, 0x1071F9C0, 0x1071F9D0, 0x10721160, 0x107211D0 (and the
`core::RefAssign<FrameController>` COMDAT copy at 0x1071F4B0, which carries no annotation).

**The three ways the box and centre accessors were closed (2026-10-16, second session).** 0x1071B130 / 0x1071B170 /
0x1071EF00 / 0x1071EF40 / 0x1071EF80 are all component assignments (`box->max.x = bounds.max.x;` ...), not struct
assignments; the two *out* accessors (0x1071B130, 0x1071EF00) additionally need two `math::Vector*` locals
(`math::Vector* outMax = &box->max; math::Vector* outMin = &box->min;`) before the copies: without them the compiler
hoists the first `fld` above the load of the argument and the function stops at 83.3 %. `Skin::GetCentre`
(0x1071F9D0) copies a fourth component past the `math::Vector` its slot is declared with, so it is written
`centre[0].x = this->centre.x; ... centre[1].x = this->centre.w;`.

**The three ten-bit packers (0x1071F060 / 0x1071F180 / 0x1071F2A0)** take three float pointers and pack the same
component of the first, the third and the fourth lane of the second: `(v + 1) * 512 + 0.5` for the first two (from
[-1, 1]), `v * 1024 + 0.5` for the third (from [0, 1]), each clamped to 0x3FF by an *unsigned* compare, and
`(unsigned)second[3]` in the top two bits. The final word is built with `+` (the engine emits `add`, not `or`):
`(((((iw << 10) + (iz & 0x3FF)) << 10) + (iy & 0x3FF)) << 10) + (ix & 0x3FF)`.

**What the skinning paths are built on (recovered while attempting 0x1071B9A0).** `SkinVertex` (0x50 bytes, declared
in `pure3d/primitive.h`) is four 16-byte rows - position, normal, tangent, a fourth the paths ignore - and four
`unsigned short` bone indices at +0x40. The bone matrices are `Pose::mData.mSkinMatrices`, i.e. `*(pose + 0x38)`
(`SkinState::pose` is the member at +0x70, now typed `Pose*`). A path loops over the vertices, loads the four rows of
the bone's `math::Matrix` with `_mm_load_ps`, blends them with `BlendRows4` (position, through the 4x4) and
`BlendRows3` (the two directions, through the 3x3) - the two helpers must be `__inline`, otherwise the compiler emits
calls to the COMDAT copies - fixes the fourth lane of each result by hand through `((float*)&r)[3]`, stores the three
rows, and accumulates `_mm_max_ps` / `_mm_min_ps` of the first row into two `__m128` locals that start at -1e12 and
+1e12 (`_mm_set_ps` with four equal constants) and end up in the box at +0x2C4 (min) / +0x2D0 (max) as six `movss`.
The assert of the paths is `OLD_ASSERT_AT(SKIN_FILE, <line>, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices)
& 0x0F) == 0", "Bad Skin bone matrices ptr")` with `SKIN_FILE` = the unit's own path; the per-site `static bool` it
leaves behind is a flag of our own unit and needs no symbols.txt entry.

Not done, with the reason:

- 0x1071F860 SkinState::SetController1: the very same code as 0x1071F880, but its `core::RefAssign` copy is
  0x10707710 (another unit), so `controller1` must be declared with the type that instantiation belongs to before the
  call can be written; `core::RefAssign<FrameController>` only reaches 0x1071F4B0 (objcmp reports 1 target differ)
- 0x1071F840 SkinState::SetExpressionState: `core::RefAssign(expressionState, ...)` needs a complete
  `pure3d::ExpressionState`, which no header in the tree defines yet (only a forward declaration)
- 0x1071ED40 / 0x1071EFD0 / 0x1071EFF0: the three one-line wrappers on the pointer at +0x148; its class is the one
  behind 0x10626860 / 0x106268D0 / 0x10626950 (the pddi dx9 unit, 0x106258D0 `PrimBuffer::Unlock` next door is a
  different layout: +0xC owner, +8 locked, +0x11C vs +0x14 and +0x2C)
- 0x1071F3C0 - 0x1071FCC0 (about 30 functions, 4 - 92 bytes): COMDAT copies of a six-field ring/table class
  (+0 valid, +4 pointer, +8 / +0xC / +0x10, +0x14 count) and of `core::SafeRelease<T>`; the template arguments are
  not readable off the bodies (identical code) and have to come from the callers or from other units

**The box and centre accessors are matched now** (0x1071B130, 0x1071B170, 0x1071EF00, 0x1071EF40, 0x1071EF80, all
100 % on 2026-10-16, third session): the component-wise copies of the "three ways" above are what they needed, and
no user-defined `operator=` was invented. The NONMATCHING list those five sat in was stale.

**The skinning paths' source shape, settled (2026-10-16, third session).** Every one of the 21 large paths is the
same skeleton - widen the vertex's rows, blend one bone's four rows per lane of a weight vector, fix the fourth lane
of each result by hand, store three rows, accumulate the first row into the box - and four details of it are what
the engine's bytes ask for. Measured with variants of 0x1071B9A0 compiled on their own:

- the two box accumulators are **`math::Vector4` locals** (`math::Vector4 maxBounds(-1e12f, -1e12f, -1e12f,
  -1e12f);`), not `__m128` from `_mm_set_ps`: `_mm_set_ps` / `_mm_set1_ps` / `_mm_setr_ps` all store their four
  lanes in *descending* address order and then copy the vector to the local, where the engine stores them
  **ascending** with no copy - which is `Vector4(float, float, float, float)`'s four member assignments. The
  accumulation itself is `*(__m128*)&maxBounds = _mm_max_ps(*(__m128*)&maxBounds, r0);` and the box write then reads
  `maxBounds.x` / `.y` / `.z`;
- the loop is **`for (unsigned int i = count; i > 0; i--)`** over a copy of the `int count` argument: the engine's
  guard is `test eax, eax` + **`jbe`** (an unsigned compare), where `while (count != 0)` gives `je` and
  `while (count > 0)` on the signed argument gives `jle`;
- the matrix rows are passed to the blend helpers **straight from memory** (`BlendRows4(_mm_load_ps(bone.m[0]), ...)`)
  rather than through `__m128 m0..m3` locals. This one matters most: with the locals the compiler loads all four
  rows up front, and it then allocates the two blend temps and the first two rows *mirrored* (the x broadcast to
  xmm7 where the engine has xmm6 and row0 to xmm3 where the engine has xmm4), which is the 18 % the second session
  reported. Passing the loads inline makes the whole loop body **come out instruction for instruction**, the x
  broadcast in xmm6, y in xmm7, row0 in xmm4, row1 in xmm3, row2 in xmm5, row3 in xmm0;
- `_mm_empty()` sits between the loop and the box write, in 0x1071B9A0 and in 0x1071B610 (and 0x1071C0C0) alike.

What is left of 0x1071B9A0 is its frame: the engine spills **both** `this` and `matrices` (0x74 bytes of frame,
`matrices` re-read as `[esp+0x18]` in the loop and the bone address materialised in edx/edi), this compiler keeps
`matrices` in `ebx`, folds it into the addressing modes and needs 0x64 bytes, which moves the whole function.
Making the loads inline made it *worse* positionally (13 %) than the locals were (18 %) even though the loop body
is now right, because the frame is 16 bytes shorter and everything after shifts.

(Superseded by "Skinning paths and bone-row blenders, matching session" below: seven of these paths match since.)

**The 19 skinning paths that are left (0x1071B610, 0x1071BBD0, 0x1071BEE0, 0x1071C0C0, 0x1071C390, 0x1071C530,
0x1071CA40, 0x1071CDC0, 0x1071D1B0, 0x1071D440, 0x1071D770, 0x1071D960, 0x1071DD60, 0x1071DFF0, 0x1071E390,
0x1071E5D0, 0x1071E8F0 and 0x10720CF0) are not reconstructed.** They are 500 - 1100 byte SSE loops of exactly the
family the four details above settle - 0x1071C390 is the one-bone case (four rows widened by one bone's 4x4, the
position through `BlendRows4`, the normal and the tangent through `BlendRows3`, three `movups` stores, the same
box), 0x1071B610 the four-bone one whose weights are the vertex's own fourth row at +0x30 and whose matrix is built
by blending four bone matrices' *rows* with those weights by the same `BlendRows4`, and the rest the same with the
expression, the second pose and the vertex-format flag of 0x10720CF0's six-way dispatch switching between them.
0x10720CF0 itself is the one that is not a loop at all (its layout is readable in the pseudocode: the pose's vertex
declaration, the lock, the two asserts at 0x87B / 0x880, the three offset triples at +0x2E8 / +0x300 / +0x318 and
the `SkinJobEntry` push at +0x33C). Writing them is not the work; the work is the frame each of them ends up with,
and that is the wall below, so the session stopped rather than write nineteen functions it could not close.

NONMATCHING:

- 0x1071ED50 Skin::Draw: register allocation (the engine's state in edi, skin in esi, binding source in ebx and
  group count in ebp are our esi, edi, ebp, ebx) plus the tail the engine clones into the blend path (the nine
  argument pushes of its PrimDrawDesc, the count as the constant 3 there and in ebp in the other path, 29 bytes we
  do not emit); declaring the source before the groups and the count, the one thing the engine's instruction order
  suggests, keeps the shape and only moves the percentage down to 16.7 %. 21.6 %
- (matches since, see the matching session below) 0x1071B9A0 SkinState::Unknown1071B9A0: register allocation (the engine spills `this` and `matrices`, we keep
  `matrices` in a register and fold it into the addressing modes), 13 %, best 18 % with the rows in locals
- 0x1071B310 / 0x1071B490 BlendBoneRows / BlendBoneRowsWide: register allocation, 21 %. The body is the engine's
  block for block (one lane of the weights widened per phase, the four rows of one bone multiplied by it, the first
  phase storing and the other three accumulating into memory) and there is not a branch in it, but the engine
  re-reads every one of its seven argument pointers from the stack once per phase (45 bytes of reloads this
  compiler does not need) and materialises the first bone's address in edx, so its allocation cannot be
  reproduced from the source. Both take the same shape: `(const <vertex>*, const math::Matrix*, const
  math::Vector4* weights, math::Vector4* row0..row3)`, the vertex's four `unsigned short` bone indices at +0x40
  (SkinVertex) resp. +0x50 (SkinVertex2, one more row of four floats, 0x60 bytes).

### Skinning paths and bone-row blenders, matching session (2026-10-18)

Match (100 %, byte for byte): 0x1071B9A0, 0x1071BEE0, 0x1071C390 (one bone each; three, two and one vectors),
0x1071D770 (one bone, the position with the expression's offset), 0x1071DD60, 0x1071E390, 0x1071E8F0 (one bone with the
vertex record's second position; the skinned delta is the last output). What the engine's bytes ask for, and what the
earlier sessions took for an allocator wall:

- The box accumulators are **two `__m128` locals filled lane by lane through float casts**
  (`((float*)&maxBounds)[0] = -1e12f; ...`, then `maxBounds = _mm_max_ps(maxBounds, r0)` and the six lane reads at the
  end). With `math::Vector4` locals the compiler gives the blended result its own stack slot; with these the result
  shares the slot of the accumulator that lives in a register in the loop, which is the 0x34 / 0x74 byte frames of the
  engine.
- The matrix rows the three blends use are **references to the bone's memory**: `const __m128& m0 = *p++;` ... (four of
  them). The loads then stay where they are used and the pointer walks the rows (the `mov edx, eax; movaps xmm4,
  [edx]` copies of the engine's loop are the post-incremented addresses). Value locals (`__m128 m0 = *p++`) and the
  `_mm_load_ps(bone.m[0])` form all come out different, and every spelling that only reorders operands or statements is
  canonicalised by the compiler to the same code.
- The output pointer is a **local copy** of `out` (`dst`), which moves the load of the argument to where the engine has
  it; for the paths that add the expression's offsets it is `__restrict` as well, because the offsets those paths read
  every pass do not change and the engine's loop hoists them (0x1071D770 reads three floats before the loop).
- The offset paths use the other loop shape, **a guard on the unsigned count followed by `do { } while (--i)`** with
  `unsigned int i = count;` inside the guard (`if ((unsigned int)count > 0)`: `jbe`), which changes the allocator's
  choice of registers for `this` and the output pointer; the plain paths match with `for (unsigned int i = count; i > 0;
  i--)`. The offset locals are `math::Vector4` with only `w` set before the loop (the zeros of `x`, `y`, `z` are dead
  stores the engine does not have).
- In the wide paths the delta's input (`offset + position`) is computed right after the vertex rows are loaded and before
  the matrix rows; swapping that order costs the match.

Not matched: 0x1071D1B0 (96 %; everything including the loop is the engine's, only the order of three instructions of the
loop pre-header differs: the copy of the count, the scalings of the two strides and the load of the max accumulator),
0x1071CA40 (24 %: the offset locals and the scalar spills are laid out differently, the frame has the engine's size) and
the nine four-bone paths (0x1071B610, 0x1071BBD0, 0x1071C0C0, 0x1071C530, 0x1071CDC0, 0x1071D440, 0x1071D960,
0x1071DFF0, 0x1071E5D0). Findings for the four-bone blend, for whoever continues:

- The engine's blend is bone after bone through four pointers that walk the rows (`*p0++` chains: base add, then
  `add reg, 0x10` between the loads), the sums are `((a*x + b*y) + c*z) + d*w` per row, and the loads stay next to their
  uses (the translation row of the first bone is even delayed until the second bone's rows are done). Our compiler
  hoists all sixteen row loads of such a chain to the top of the loop and spills them (frames 0x84 - 0x134 against the
  engine's 0x44); this is the same for `__m128` values, for `_mm_load_ps` of a float pointer and for named locals. With
  displacement addressing (`_mm_load_ps(k.m[r])`) the frame is right (0x44) but the compiler turns the sum row-major
  and no pointer chain is left; with references the row addresses are kept in registers and spilled (`mov [esp+x],
  ecx`).
- The nearest form is the engine's `BlendBoneRows` body inlined with the four rows as `__m128` locals written through
  pointers (`BlendBoneRowsInline` in skin.cpp): the instruction multiset (counts of every opcode) is the engine's apart
  from two spills, the frame and the order of the loads are right, 42 % of the bytes match for 0x1071C0C0.
- 0x1071B310 / 0x1071B490 `BlendBoneRows` / `BlendBoneRowsWide` have no caller anywhere in the image (they are unused
  out-of-line copies of the code the four-bone paths carry inline). The engine re-reads the weights in every phase, a
  store through a row pointer may change them, and the source now does the same; what does not come out is the first
  phase (the engine loads the first row before the weights and keeps the loads apart from the multiplies) and where the
  `add reg, 0x10` increments of the bone pointers land. A search over the spelling of the row loads (value, reference,
  `_mm_load_ps` of the pointer, separate increment statements, in any mix per row) reaches 68 % of the bytes with the
  engine's size, but only with spellings no author would have written side by side, so the committed body keeps the
  uniform 45 % form.

0x10720CF0, the job dispatcher, is not reconstructed (not done). Its shape: the byte at +0x2AE selects whether anything
runs; the pose index at +0x2C0 is advanced (`++index; if (index > 0) index = 0`) after virtual slot 9; the pose's vertex
buffer is locked into a `dxVertexDeclaration`-sized description (`PrimBuffer::Unknown10625FA0` fills a
`ShaderParameters` first, 0x10625F00 locks), two asserts check the destination stride and the source pointer, the three
offset triples at +0x2E8 / +0x300 / +0x318 (base, base, base + stride * count, with the strides at +0x2F8 / +0x310 /
+0x328) are set from the lock's base, and then either the job is queued (the global byte at 0x11137804: the record at
+0x330 gets the lock's data, the expression's three offset pointers and the two flag bytes at +0x2FC / +0x314, and the
entry at +0x33C is pushed on `gPendingSkins`) or the path is called directly. The direct branch is the tree the old notes
describe: flag +0x2FC clear: positions only, +0x74 (the expression) null and bit 0x20000000 of the lock description's format word clear
-> 0x1071C0C0 / 0x1071C390 (the byte at +0x298 of the primitive `GetPrimitive` returns selects four bones when clear, one bone when set), wide ->
0x1071E5D0 / 0x1071E8F0, expression set -> 0x1071D440 / 0x1071D770; flag +0x314 clear (two vectors): 0x1071BBD0 /
0x1071BEE0, wide 0x1071DFF0 / 0x1071E390, expression 0x1071CDC0 / 0x1071D1B0; otherwise three vectors: 0x1071B610 /
0x1071B9A0, wide 0x1071D960 / 0x1071DD60, expression 0x1071C530 / 0x1071CA40. Missing before it can be written:
the types behind 0x10625F00 (the lock), 0x107202B0 (a Skin method taking the second `ShaderParameters`), 0x106E2A30 (a
method of the pose at +0x70) and the job record at +0x330.

- (op-finish) 0x1072E3E0 `GpuSkin::GpuSkin` **matches**: the centre is set with `centre.Set(0.0f, 0.0f, 0.0f)` (the
  inline's three stores keep the parameters' push behind them).
- (op-finish) 0x1071D1B0 stays NONMATCHING (96.5 %): declaring the counter outside the guard, its type, the loop's
  decrement form, the order of the stride declarations, of the two offset tests and of the loop's loads all leave the
  copy of the count ahead of the two stride scalings in the pre-header (the engine scales the normal stride, then the
  position stride, then copies the count). The nine four-bone paths and 0x1071CA40 not reworked (see above);
  0x10720CF0 not reconstructed (its callees' types: 0x106F2DE0, 0x10625F00, 0x1071F020, 0x107202B0, 0x106E2A30).
- (mp-skin) 0x1071D1B0 **matches**: the offset paths' loop is `for (unsigned int i = 0; i < (unsigned int)count; i++)`
  (the induction variable is replaced by a down counter, which is created after the loop-invariant stride scalings, in
  the engine's order), not the guard plus `do { } while (--i)` the earlier sessions wrote.
- (mp-skin) 0x10720CF0 `SkinState::Unknown10720CF0` (the job dispatcher) is written and compiled in as EQUIVALENT (265
  instructions, same size, frame and registers as the engine's; 91.3 % of the bytes, 96 % of the instructions): what is
  left is scheduling only (the loads and the multiply of the three stream set-ups come out in another order, the flag
  test in front of the third one and the store / load pair of the queueing branch too; no statement order, local or
  expression form moved them). The types it needed: the buffers at +0x2B0 are `PrimBuffer*` (`dxVertexBuffer`:
  `Lock` 0x10625F00 takes a `dxVertexDeclaration` that receives the declaration, the locked block in `unknown108` and the
  flags; `Unknown10625FA0` takes the `ShaderParameters` it fills), 0x107202B0 is `Skin::GetParameters(ShaderParameters*)`
  (a copy of the skin's own parameters; the word at +0xC of the copy is the format, bit 29 = wide vertex record),
  0x106E2A30 `LockableRefCounted::Lock()`, the three streams at +0x2E4 (`SkinStream`, 0x18 bytes: enabled, offset, start,
  current, end, stride), the job record at +0x330 (`SkinJobData`), the pending flag at +0x32C and the byte at +0x298 of
  the skin (one bone each when set). `gSkinAsync` (0x11137804, true) and `gSkinQueuedCount` (0x1128180C) are skin.cpp's
  globals. The counters use `_InterlockedIncrement` / `_InterlockedDecrement` (the exchange-add form puts the operands
  in the other registers).
- (op-map1) 0x10720CF0 stays EQUIVALENT, now 97.5 % (was 91.3): the first two streams are set up through their address
  (`BeginStream(&streams[i], base, count)`, an inline taking a `SkinStream*`), which keeps the next stream's loads
  behind the stores as in the engine; the third one written on the member directly. Left: the test of `gSkinAsync`
  comes after the third stream's stores (the engine: before them) and the format word's load in the queueing branch
  after the store of `hasTangents` (the engine: before it). No captured states.
- (op-map2) The four-bone paths not reworked. Reading the engine's 0x1071C0C0 / 0x1071E5D0: the accumulators it keeps
  on the stack are spill slots (the blended rows are never stored as such; the slots are shared later with the
  results whose fourth lane is written), and the vertex position is loaded between the second and the third bone.
- (op-map2) 0x10720CF0 stays EQUIVALENT, now 99.1 %: `gSkinAsync` is a file-level `static` (the dispatcher is the only
  code that reads it), which lets the compiler schedule its test ahead of the third stream's stores as the engine does;
  the third stream is written through a local `SkinStream*`. Left: the format word's load in the queueing branch after
  the store of `hasTangents`. Note for the hybrid build: the static is our own copy (the engine's byte is no longer read).
- (op-map3) 0x10720CF0 stays EQUIVALENT (99.1 %). On small units this compiler never schedules the load of an
  address-taken local above a store through a pointer it loaded from memory, whatever took the address (a callee of
  the unit or another, noalias, a reference) and however the record is declared (restrict member or local, volatile);
  a local for the format between the two flag stores puts the load first but rotates the registers (73 %); barriers
  after every statement and all orders of the queueing stores leave 99.1 %. The four-bone paths not reworked.
- (op-map4) 0x10720CF0 stays EQUIVALENT (99.1 %). The load that is out of place is the one a load-before-store
  dependence pins: in a harness that mirrors the queueing branch this compiler never lifts a load of an address-taken
  local above a byte store through a pointer it read from memory, whether the record's pointer or its members are
  `volatile`, whether the local was passed by pointer, reference, as a by-value return or only to its constructor,
  and whether the format is a bit-field; with the format read into a local (or an inline helper's argument) before
  the flags' stores the load comes first but both flag copies turn into `movzx` (73 %), unless all three flags are
  one inline call's arguments (the byte copies stay, 75 %, the loads all ahead of the stores). `Skin::GetParameters`
  (0x107202B0) **matches** and is defined in the unit now; it is `*parameters = this->parameters` with the skin's
  `ShaderParameters` at +0x20 (0x118 bytes, up to the draw data at +0x138): the `core::AsyncTaskJob` and the pose
  that were listed there belong to the `SkinState` (+0x20 and +0x70; the task's callback is the RTTI's
  `SkinState::AsyncTaskAdaptor` and carries the state at +4), so `SubmitTask` (0x1071EAE0) is a `SkinState` method
  and the job entry's second word points at the state.
- (op-map4) The nine four-bone paths stay NONMATCHING but their shared blend (`BlendBoneRowsInline`) now follows the
  engine's loop shape, measured by the instructions each loop shares with the engine's in its order (a diff of the
  instruction lists; objcmp's byte percentages fall when the loop grows by a few copies): 1509 of the nine loops'
  2088 instructions, from 1284. What moved them: the vertex's vectors loaded before the blend (the engine keeps the
  position in xmm1 and spills accumulators instead), the first bone's three rotation rows read before its products
  and its translation row only after the second bone's rotation rows (the translation accumulator starts as
  `b13 * w1 + b03 * w0`), the first bone's products in the order 2, 0, 1 (the third row's product is the one the
  engine spills), the weights read from the vertex again at each bone (one load comes out, the splats stay at their
  bones), the rows of the second to fourth bone as named values read just before their products (the second bone's
  first one after the first bone's products). 0x1071C0C0 has the second and third bone's blends instruction for
  instruction (158 of 190; the position-first form of its old 63 % body had 125). Left in all of them: which
  products are computed into the row's register and which into a copy of the splat (the engine: the first and last
  bone in place, the middle two through a buffer register), and the last bone's loads straight into the result
  registers; operand orders, `__m128*` rows in the template (much worse: 83 of 190), in-place `row = row * s`
  spellings, a product variable and `w` loaded once do not change that. The standalone blenders 0x1071B310 /
  0x1071B490 are 60 % (from 45 %): the first bone's first three rows through one variable (the engine keeps them in
  one register and multiplies into a copy of the splat), the rest read inside the products.
- (mp-skin) 0x1071CA40 stays NONMATCHING at 99.4 % (the engine's instructions, frame and stack slots; three instructions
  differ because the tangent's and the normal's offset vector trade xmm2 / xmm3 in the loop's head). What made it: the
  loop `for (unsigned int i = 0; i < (unsigned int)count; i++)`, and the tangent as ONE variable that is loaded, has
  its fourth lane read at once (`float tangentW = ((float*)&v2)[3];`), is added to in place and then blended into its
  own result variable: the engine's v2 / r2 share one slot, the offsets get its slot order, and the lane is saved
  before the vector is overwritten. Statement order, operand order, `.m128_f32`, locals of other types, dead locals
  and padding declarations do not move the last register pair. The same tangent form is written into 0x1071C530.
- (op-map1) 0x1071CA40 **matches**: the three offset vectors are `__m128` locals filled lane by lane through float
  casts (like the box accumulators) and added as values (`_mm_add_ps(v2, tangentOffset)`); as `math::Vector4` locals
  read back with `_mm_load_ps(&offset.x)` the tangent and the normal's offset trade xmm2 / xmm3.
- (op-map1) The four-bone paths stay NONMATCHING, but closer. Their real sizes are larger than symbols.txt had: the
  epilogue after the last bounds store (`pop esi; pop ebx; mov esp, ebp; pop ebp; ret 0xC`, reached by the early return
  too) belongs to them (0x1071B610 0x387, 0x1071BBD0 0x30F, 0x1071C0C0 0x2CD, 0x1071C530 0x505, 0x1071CA40 0x379,
  0x1071D960 0x3F3, 0x1071DFF0 0x391, 0x1071E5D0 0x31B; corrected in symbols.txt and functions.tsv). The blend that comes
  closest takes the rows as values walked with `*p++` and writes the four blended rows through pointers to `__m128`
  locals (`*q0 = _mm_mul_ps(b00, splat)`, `*q0 = _mm_add_ps(_mm_mul_ps(b10, splat), *q0)`): 0x1071C0C0 63.2 % with one
  uniform spelling (was 43.2). A genetic search over per-bone spellings (value / reference / indexed rows, loads before
  or between the products, splats inline or as locals, where the vertex loads sit) reaches 59 - 73 % for the others
  (0x1071DFF0 72.9 %, 0x1071D440 / 0x1071E5D0 66.4 %), always with the engine's size but never its spills: the engine
  delays the first bone's translation row product until after the second bone and spills an accumulator to the stack,
  this compiler schedules every DAG it is given without that spill.
- (mp-skin) The slot order of equal-weight locals (the engine's stack table is sorted by reference count; ties come out
  in an order the source's statement order, declaration order and names do not change) and the register a vector
  gets can depend on declarations in the headers a unit includes: a new type name in primitive.h flipped two locals of
  Context::LoadDebugFont (0x1070FC90) until the SkinState buffers stayed a cast instead of a union member. After any
  change to primitive.h / primstream.h / pose.h compare the progress count (`ninja report progress`), objcmp does not
  see every function the objdiff count does.
- (mp-skin) The four-bone paths (0x1071B610, 0x1071BBD0, 0x1071C0C0, 0x1071C530, 0x1071CDC0, 0x1071D440, 0x1071D960,
  0x1071DFF0, 0x1071E5D0) still do not match: 17 - 43 %. Their loops now are the engine's (for-up counter; the pre-header
  and the guard come out byte for byte in 0x1071C0C0 up to the first bone's loads). Measured on 0x1071C0C0 with
  tools/permute-style searches over the source's spelling (statement order of the 16 row products, value / reference /
  inline loads, one or four weight loads, splats ahead of the products, the translation row last or merged, rows as
  `__m128` locals, a `math::Matrix`, `math::Vector4`s, pointers or SSA values): every form reaches 60 - 72 % of the
  instructions; pure SSA forms (no store through a row pointer) make the compiler hoist all sixteen row loads and spill
  (frame 0x134, 909 bytes), the memory forms keep the loads at their products; computing all four splats before the
  products gives the engine's register for the first row (xmm5) and the first twelve instructions of the loop, but then
  the frame is a slot too big. The engine's schedule loads the first bone's three rows and the second bone's first row
  before the first splat, multiplies the third row first, spills it, and computes the translation row's first product
  after the second bone's last row. The standalone BlendBoneRows (0x1071B310) makes its first splat in place and
  multiplies the first three rows as `copy of the splat * row` and the fourth as `row * splat`; the spellings reach one
  or the other, never both (88 % of its instructions is the best).
- (mp-skin) 0x1071D440's position offset has no stride (one offset for all the vertices: the engine reads the three
  floats once, ahead of the loop, like its one-bone sibling 0x1071D770); the earlier source gave it the stride of the
  paths with several offsets. Its pre-loop part is the engine's now (71 instructions identical), the blend is not.
- (op-eq1) Six of the nine four-bone paths are EQUIVALENT now (compiled into the hybrid DLL), proven by difftest on
  states from the game: 0x1071B610 (29.3 %, SAME on 10 captured states), 0x1071C530 (29.4 %, SAME on 3 captured
  states), and with states borrowed from those two (the paths take the same arguments and read the same vertex
  record; the engine's own run completes on them) 0x1071BBD0 (35.3 %, 13 states), 0x1071C0C0 (40.5 %, 13),
  0x1071CDC0 (33.2 %, the 3 of 0x1071C530; the 10 of 0x1071B610 have no expression) and 0x1071D440 (37.5 %, the
  same 3). The source is the mp-skin / op-map4 one; what differs from the engine is the register and spill allocation
  of the blend only, the operations and their association order are the engine's. Unreached on every path: the
  assert's report (the matrices are aligned in every state) and two bytes of jump padding. The three wide paths
  0x1071D960 / 0x1071DFF0 / 0x1071E5D0 stay NONMATCHING for lack of states: the narrow states cannot be borrowed
  (read as the 0x60-byte record the bone indices come from other fields, and the engine's run leaves the saved
  pages), and the paths never ran in the captures. The misalignment canary (local/scratch/emu/skin_b6c1c8c.obj)
  still reports DIFFERENT.

## pure3d/pddi/src/dx9 (the Direct3D 9 back end, 0x1061B530 - 0x1062B800): started, 22 functions match

The units are named by the two assert paths the range keeps (`dxdefaultpoolmanager.cpp` in 0x106238B0 and
`dxvertexdeclaration.cpp` in 0x1062B170 / 0x1062B710); the others are guessed from their contents. Done so far:

- `pure3d::pddiObject` (RTTI; base `core::IRefCount`, four slots: `0x10611FC0` AddRef, `0x10611FD0` Release,
  `0x10611AF0` the destructor the derived ones call, `0x10611B00` slot 3): the constructor `0x10611F90` installs the
  `pddiObject` vftable and clears the count. All four live in the pddi base unit and are only mapped.
- `pure3d::dxVertexDeclaration` (0x10625AC0) and the manager's statistics dump (0x1062B710) in
  `src/code/pure3d/pddi/src/dx9/dxvertexdeclaration.cpp`.
- `pure3d::dxTexture` is laid out now, from its destructor and its two creations: the description it was asked for
  is copied into it at +8 (0x38 bytes, 0x1061C8F0 checks it and resolves its format into the Direct3D one at +0x58),
  +0x40 is the pool manager's `dxSurface` record (0x20 bytes, the surface at +8), +0x44 the level records (one
  8-byte `{count, data}` per mip level, the data being 16-byte `{width, height, pitch, size}` records),
  +0x48/+0x4C/+0x50/+0x54 the Direct3D texture of each kind, +0x5C the pool, +0x68 a `D3DLOCKED_RECT` and +0x70 a
  `D3DLOCKED_BOX`, +0x80 the bytes it counts for and +0x88/+0x8C the texture it was copied from and the one copied
  from it. 0x1061C400's constructor is dxTexture's whole layout in one place.
- The four-byte holders release through one function template `ReleaseRef<T>(T**)`; the compiler emits it out of
  line in the texture unit (0x1061CA90 - 0x1061CB10, one copy per type: two pddi types through their virtual
  Release, three Direct3D interfaces through the interface's own) even though the destructor's own call sites are
  inlined by the engine too. `AssignRef<T>(T**, T*)` (0x1061CB50 / 0x1061CB80) is its holding counterpart.
- `pure3d::dxTexture::~dxTexture` (0x1061CBE0), the five `ReleaseRef` copies and the layout above, and the
  constructor 0x1061C400. That one proves the description has a constructor of its own: the engine stores the
  description's fourteen fields **before** the object's other members, which a constructor body (it runs after the
  initialiser list) cannot do — `TextureDescription` therefore carries an inline default constructor that sets
  `unknown20 = -1`, `unknown24 = -1`, `unknown28 = 1`, `unknown34 = true` and zero elsewhere.
- `pure3d::dxIndexBuffer::Create` (0x10626770): the usage bits go through a **named local** (`unsigned int flags =
  description->usage;`), which is what makes the engine's register test (`test al, 1`) instead of a memory test, and
  the format is declared before the usage flags.
- 0x1061CA00 (`dxTexture::Unknown1061CA00`): the surface this texture was made from is stretched into its first
  level with a linear filter when the caller asks for one. Two findings of it: an int-returning helper whose callers
  test its **low byte** (`test al, al`) keeps its answer in a `char` local — a `bool` return would make the helper
  itself emit `mov al, 1` and stop matching — and the format test is `char supported =
  IsTextureFormatSupported(d3dFormat); if (supported == 0)`.
- `pure3d::dxVertexBuffer::dxVertexBuffer` (0x106262D0), `dxContext::NewTexture` (0x1061B550 / 0x1061B5A0),
  `dxContext::NewVertexBuffer` (0x1061B600), `dxContext::NewIndexBuffer` (0x1061B660), the two `dxContext`
  accessors 0x1061B530 (`+8`) and 0x1061B540 (the device at +0xC), and `IsTextureFormatSupported` (0x1061C360), the
  format test the two texture creations open with. That one is an **if-chain of `==` joined by `||`**, not a
  `switch`: the values 0x46 - 0x53 are dense enough that a switch becomes a jump table, and it returns a 32-bit 0 /
  1 (`mov eax, 1`), not the `bool` its callers' `test al, al` suggests.
- Two more findings of the unit: the four-byte member holders of `dxTexture` are released by **free function
  templates** `ReleaseRef<T>(T**)` (the argument is on the stack, so these are not destructors; one copy per T,
  0x1061CA90 - 0x1061CB10), and 0x1061C8F0 validates and copies a texture description into the object.

New headers: `code/pure3d/pddi/dx9/d3d9.h` (the COM interfaces; the toolchain has no SDK, and the engine's calls
are the C form `device->lpVtbl->Method(device, ...)`, so the entries are `__stdcall` and the interface is pushed),
`dxtexture.h`, `dxindexbuffer.h`, `dxvertexbuffer.h`, `dxcontext.h`, `dxprimstream.h`; `pddi.h` gained `pddiObject`
and `pddiPrimStream` and split `pddiBaseContext`'s `unknown4[0x10]` into four named words (the dx9 factories pass
the third).

NONMATCHING:

- 0x1061CD70 `dxTexture::Create`: register allocation, 26.4 %. The whole body is there in the engine's order (the
  scale path, the level build, the three texture kinds, the pooled surface path and the retry loop) and within a
  byte of the engine's size, but the engine keeps `usage` in `ebp` and `&this->description` in `edi` where this
  compiler does the opposite, and it keeps `(usage >> 1) & 1` as a shift where this compiler folds it into
  `test byte [this + 0x20], 2`. Walking the condition through `% 2`, a named shift result, a named `bool` and
  swapping the `pool` / `usage` declarations changes none of it.
- 0x1061D010 `dxTexture::Create` from an image: register allocation, 30.3 %. Same cause: the engine keeps the level
  in `edx` and reloads it from its argument slot after every Direct3D call, this compiler caches it in a
  callee-saved register, which moves every instruction behind it.
- 0x1061C600 `dxTexture::Lock`: register allocation, 17.9 %. The checks, the three lock paths (volume box, cube
  face, the system-memory copy of a 2D texture) and the lock description handed back are all there; the register
  difference above shifts the body.
- 0x106266D0 `dxIndexBuffer::dxIndexBuffer`: register allocation, 62.3 %. Every store is in the engine's order (the
  initialiser list, then -1 at +0x34, then the six words of the state block), but the engine clears the state block
  with a zero it materialises in `eax` (`xor eax, eax` after the state's constructor call) where this compiler
  reuses the zero the initialiser list left in `ebx`, and it schedules the -1 store in front of them.
- 0x10623FB0 `RestoreDefaultPool` **matches** (what it took is in the last notes of this section).
- 0x1062AA90 `dxPrimStream::dxPrimStream` matched after all (the relocation into the buffer pool resolves to the
  engine's `operator new[]` now): it is 100 % against 0x1062AA90 and no longer counted as NONMATCHING.

Not done (each is a large function of a unit whose other members are still missing):

- `dxdefaultpoolmanager.cpp` is reconstructed now (`src/code/pure3d/pddi/src/dx9/dxdefaultpoolmanager.cpp` and its
  header): 0x10623860 (the D3DERR text) and 0x106238B0 (the allocation failure report) are **static helpers** whose
  HRESULT arrives in `edi` — the static declaration is what makes that convention (`/O2` gives an external function
  its arguments on the stack) — and the four pool allocations 0x10624990, 0x10624A70, 0x10624B10, 0x10624BA0,
  0x10624C60 and the release 0x10624D10 followed them in. The manager is the singleton at 0x11276DA4: five
  `{begin, end, capacity}` arrays at +0x00, +0x10, +0x20, +0x30, +0x40 (one per texture, vertex buffer, index
  buffer, render target and depth/stencil surface, each followed by a word the engine never touches — the shared
  `container::ArrayDynamicNew` is 0xC bytes, so the manager declares the padding, as the Lua script manager's own
  arrays do), the D3D device at +0x50 and a byte at +0x54; the lock is `0x11276D8C`. The pool works through the
  device's global at 0x11276D38, and the entries it hands out are {width, height, levels, float scale, usage,
  format, texture slot, surface slot} for a texture (0x20 bytes), {length, usage, fvf, buffer slot, data} for a
  vertex buffer (0x14), {length, usage, format, buffer slot} for an index buffer (0x10), {width, height, float
  scale, lockable, format, multiSample, surface slot} for a render target (0x1C) and {width, height, float scale,
  format, multiSample, surface slot} for a depth/stencil surface (0x18). 0x1061B140 (the multisample mode of a
  sample count) is declared there too, as `pure3d::GetMultiSampleType`.
- `dxdefaulttextures.cpp`: the default textures 0x1061D3A0 (NONMATCHING). The creations branch on the texture type
  at +8 (1 a 2D texture, 2 a cube texture, 3 a volume texture, through the device's +0x5C / +0x64 / +0x60), 0x1061C600
  locks a level of each kind, and 0x1061C490 lays its levels out. 0x1061CA00 is done (see above).
- `dxvertexdeclaration.cpp` 0x1062B170 (the declaration's own dump) and 0x1062B5C0 (the declaration table's lookup).
  `dxVertexBuffer::Create` (0x10626350) and its name-to-usage helper 0x10625BF0 (a file-local `static` that takes the
  name in esi) match. The helper is a chain of `else if` tests with one `return result;` after it - separate `return`
  blocks or `||` chains give another block layout. `Create` needs the byte-wide fields of `ShaderParameter` to be
  *signed* (`int unknown8 : 8`, so the kind index is read with `movsx`) and the locals declared offset, length, stride.
- the context / device-reset functions 0x10616BB0, 0x106182C0, 0x1061FB40, 0x10620A20, 0x10620B00, 0x10621060 and
  0x10623250: they belong to the big `engine::Display` / `dxContext` class at 0x10616xxx - 0x10623xxx (members up to
  +0x82C, `+0x3C` the constant table, `+0x664` and `+0x690` further state), whose layout is not recovered yet.
  0x10620A20, 0x10620B00 and 0x10623250 also take arguments in `ebx` / `ebp`, and 0x1062B5C0 in `ebx` / `ebp` again,
  so they are link-time-codegen functions on top of that.

`?Unknown1@pddiPrimStream@pure3d@@UAEXXZ = 0x1062AA20` was a **guess** and is wrong: with 0x1062AA90's vftable now
emitted, `vtcheck.py` shows the pddi stream's slot 1 holding 0x10A88350 and the dx9 stream's own override
`?Unknown1@dxPrimStream@pure3d@@UAEXXZ` holding 0x1062AC90, and both are mapped that way now. The old text:
0x1062AA90's vftable was not emitted while the
constructor is NONMATCHING, so nothing checked it against the engine's slot.

- 0x1071B9A0 SkinState::Unknown1071B9A0: the body is the engine's instruction for instruction (the loads, the two
  blends, the fourth lane, the four-lane min/max, the six stores of the box), but the compiler of the hybrid build
  allocates the two blend temps the other way round (the `shufps ..., 0` temp to xmm7 where the engine has it in
  xmm6, and the first matrix row to xmm3 where the engine has it in xmm4), which mirrors the first eight shuffles and
  multiplies of every pass, and keeps the output pointer and the vertex pointer in swapped registers (18 %). Every
  other path of the run 0x1071B9A0 - 0x1071E8F0 has the same shape, so this has to be settled once for all of them;
  a shared source or a front-end difference, not a missing piece.

Matching session (op-finish, 2026-10-18), what the engine's bytes asked for:

- 0x106266D0 `dxIndexBuffer::dxIndexBuffer` **matches**: the state block is cleared with `memset(&state, 0, sizeof(state))`
  (the zero in eax after the state's constructor), not member by member.
- 0x10620A20 / 0x10620B00 **match**: the declaration switch is an inline helper (`SelectVertexDeclaration(int)`, the
  number by value, so it is not re-read after the store to `current`) with the device in a local
  (`IDirect3DDevice9* device = gD3DDevice;`), and the batched primitive count is added through a reference
  (`float& primitives = batchedPrimitives;`), which keeps its store ahead of the load of the tracker.
- 0x1061FB40 `DrawPrimitive` **matches**: the index buffer in a local (`dxIndexBuffer* indices = desc->indices;`), the
  indexed branch first in all three tests (`if (desc->indices != 0)`), the index count as `if (desc->count != 0)
  indexCount = desc->count; else indexCount = ...GetUnknown1C();`, the techniques in a local before `Get`, and the
  device in a local in both draw branches (the plain one loads it before the switch).
- 0x10623250 `Unknown2` stays EQUIVALENT (28.7 %): the same shape as DrawPrimitive; the engine keeps the technique in
  ebp and the index buffer in a stack slot, this compiler the other way round. Its primitive count was converted as
  unsigned where the engine converts it as a signed int (`cvtsi2ss`): fixed, it differed for -1.
- 0x106182C0 stays EQUIVALENT (97.5 %): the capabilities' stores in the order 78F (through a reference), 790, width,
  height; only the height store sits one instruction early. Permutations of the present parameters (permute.py, 2500
  compilations) gave the order now in the source.
- 0x1062B5C0 stays EQUIVALENT (96.6 %): every store order, references, a constructor or `Set` for the new entry and the
  `+= users` form leave `users = 1` behind the element count.
- (op-map2) 0x1062B5C0 stays EQUIVALENT (96.6 %): the new entry declared before the search loop with `users` (and the
  element count) set there gives 20 - 44 %; `_ReadWriteBarrier()` around the stores reloads the manager (70 %).
- 0x1061C600 `dxTexture::Lock` stays EQUIVALENT (8 %): the engine has two `return false` blocks (early returns) and does
  not clear the two surface pointers; both bring it to 14.6 % only, `level` stays cached in ebx (engine: re-read).
- 0x10623FB0 `RestoreDefaultPool` **matches**: the vertex buffer's lock goes through a `void* data` local and a named buffer
  local (not a `D3DLOCKED_RECT`), the surface fix-up behind a texture's creation is written once as an inline function
  that both creation branches call (the engine keeps a copy in each branch and does not tail-merge the two
  `ReportAllocationFailure` calls), and the vertex buffer's output pointer is read as `Begin()[i]`: with the plain
  `operator[]` there this compiler turns the operands of one address in the depth/stencil loop around (`[esi+eax]` against
  `[eax+esi]`, one byte); the same single change at the index buffer's or a render target's output pointer does it too, so
  the choice is arbitrary.
- 0x1061D3A0 `CreateDefaultTextures` stays NONMATCHING (36 %, 1400 of 1517 bytes); not reworked.
- Second pass over the six (2026-10-18; objdiff's percentages are given where objcmp's position-by-position ones are
  far lower): 0x10623FB0 matches (above, 100 % over its real 1553 bytes; `functions.tsv` and `symbols.txt` had 1536, the
  shared epilogue after the last call belongs to it). 0x106182C0 stays EQUIVALENT (97.5 %, objdiff 98.7 %) after about
  1700 more compilations (every order of the capability stores and of the window-mode test, references, locals, flag
  types, the display-mode local's place): only the height store moves. 0x1062B5C0 stays EQUIVALENT (96.6 %, objdiff
  98.8 %) after about 600 (orders, copies in locals, an inline initialiser, the three spellings of the count's increment):
  `users = 1` stays behind the element count. 0x10623250 stays EQUIVALENT (28.7 %, objdiff 89.4 %): a local for the
  technique table, a conditional for the vertex count and the device taken in each draw branch give the technique ebp as
  in the engine (64.5 %) but lose the engine's order of the first two calls and the device table's single load, so the
  source keeps the plain form. 0x1061C600 stays EQUIVALENT (8 %, objdiff 81 %): the engine keeps `level` and `slice` in
  edx / ecx and reads them again after the calls, so ebx and ebp are pushed only after the checks; nothing tried
  (references to the system-memory copy, local copies, other arm orders) changes the choice. 0x1061D3A0 stays
  NONMATCHING (36 %): the engine keeps the zero in edi and the one in ebx for the whole function and sets them again
  after every fill, with different registers for each fill's width and pitch.
- (op-map1) Third pass, none of the five closes: 0x106182C0 all 120 orders of the five statements between the two
  device calls (the reference for the first store kept) give 97.7 % at best (the height store moves the other way);
  inline helpers for the stores or the window test and a struct copy of the two sizes change nothing. 0x1062B5C0: the
  entry written through a local pointer, through an inline `StartEntry(entry, count)`, with a constructor in a derived
  entry or with `users` as a member object whose constructor sets 1 all stay at 96.6 %. 0x10623250: the index buffer
  set-up in its own block, as nested tests or with the device in a local is canonicalised to the same code (28.7 %).
  0x1061C600: the usage test as its own early return gives the engine's prologue up to the level check (17.9 %, 586
  bytes) but `level` keeps ebx. 0x1061D3A0: the lock cleared through a pointer changes nothing (35.8 %); its ramp
  computes `t = x / 255` in SSE before the switch (one stack temporary the two cosine cases read) and each case has its
  own clamp tree (`v < 0` first, then `v > 0xFF` on both paths; the cosine cases cross-jump into the first two cases'
  trees), where the source has one clamp after the switch.
- (op-map2) 0x10623250 `Unknown2` stays EQUIVALENT (28.7 %): the vertex count kept in a second variable across the
  technique's Get, the shader's technique table taken inline and the index buffer read into a local for the index
  count all compile as before. 0x106182C0 not reworked (97.5 %).
- (op-map2) 0x1061C600 `dxTexture::Lock` stays EQUIVALENT, 9.7 % (was 8): the usage, level and slice checks written as an
  inline returning a bool (`CanLock`) give the engine's blocks (the locked texture's early return, one shared
  `return false` for the failed checks, the body behind them), with the surfaces uninitialised and the system-memory
  copy reached through a pointer. `level` still takes ebx (the engine: edx, read again after the calls), which keeps
  the push of ebx in front of the checks. difftest SAME (11 states).
- (op-map2) 0x1061D3A0 `CreateDefaultTextures` stays NONMATCHING, now 75 % (was 36 %, same size as the engine's): the fills
  write through a `__restrict` row pointer and read `lock.width` / `lock.pitch` in their loops (that gives the engine's
  zero in edi and one in ebx), every description sets levels, depth and format again before its texture is made, the
  ramp computes `t` before the switch and each case packs its own pixel through an inline helper, the first ramp packs
  with multiplications and the cosine ramps are `float ramp = (cos(t * f) + 1.0f) * 0.5f;` then `ramp * 255.5f` (one
  expression folds the two constants). Left: the clamp tree (the engine: `v < 0` first, then `v > 0xFF` on both paths,
  no cmov); every spelling tried folds the negative path, uses cmov / setcc or tests `> 0xFF` first.
- (op-map3) 0x1062B5C0 `FindVertexDeclaration` **matches**: a `_ReadWriteBarrier()` between the new entry's stores and
  the device call. The stores then form a scheduling region of their own and come out in the source order (the user
  count's `mov esi, 1` first, then the element count); with the device call in the same region the scheduler hoists
  the element count's store above the constant. Barriers elsewhere (before or between the stores) reload the manager
  (70 %); a volatile read of the count, a volatile device pointer, an empty `__asm` block and a device local do not end
  the region the same way.
- (op-map3) 0x106182C0 stays EQUIVALENT (97.5 %): the two capability bits as mask tests, a barrier after every statement
  and the orders of the present parameters' stores leave the height store where it is. 0x10623250 stays EQUIVALENT
  (28.7 %): the index buffer's test as nested ifs or without a local (the parameters take ebp then), the technique
  declared first or unsigned, barriers (the engine's size with one in a draw branch, 51 %) and the statement orders
  that keep the engine's call order change nothing. 0x1061C600 stays EQUIVALENT (9.7 %): barriers (14.6 % at best) and
  the orders of the box's and the lock's stores leave `level` in ebx. 0x1061D3A0 stays NONMATCHING (75.3 %): the
  engine's clamp tree is `clamped = value; if (value < 0) clamped = 0; if (value > 0xFF) clamped = 0xFF;` without the
  if-conversion of the first test (the second test copied into both paths, the zero sunk into its leaf); this compiler
  makes the first test a `cmovs` from the unit's zero register (edi) whenever one exists, and other result types,
  explicit nesting (setcc), `else if` forms and /Os, /O1, /Oy- keep a cmov or setcc.
- (op-add1) 0x1061BBC0 `Unknown1061BBC0`, 0x1061C830 `dxTexture::Unlock`, 0x10626860 / 0x10626950
  `dxIndexBuffer::Unlock` / `Lock` **match**. 0x1061BBC0 makes the one `dxDevice` (0x10 bytes, no RTTI, constructor
  0x1061BA70, global 0x11276D40) over `Direct3DCreate9(D3D_SDK_VERSION)` (import thunk 0x10A89FD0) after counting the
  start (0x10627FB0); the 0x10-byte object is what `gPddiDx` holds and what the tree declares the methods of as
  `dxContext` (Initialize 0x1061B4C0 makes the display at +8 and the 0x698-byte device context at +0xC), so the function
  hands it out as a `dxContext*`. `dxIndexBuffer::Lock`: the lock's `void* data = 0;` must be the **first** statement;
  declared after the length the compiler puts it into the dead argument slot of `lockState` (no `push ecx` frame).
  `dxTexture::Unlock` is the switch over the type in Lock's case order (3, 2, 1).

## Merge notes (2026-10-16)

- (op-map4) 0x106182C0 stays EQUIVALENT (97.5 %): a `volatile` window mode (the compare of a volatile member would
  pin the stores after it) gives a separate `mov edx, [esi + 0x20]; cmp edx, edi` (29.7 %), so the engine's compare is
  of a plain member; not reworked further.
- (op-map4) 0x1061D3A0 `CreateDefaultTextures` stays NONMATCHING (75.3 %); its unit is confirmed separate from
  dxtexture.cpp: compiled behind `dxTexture::Lock` the compiler drops the zero stores into the lock record that Lock
  never reads (1408 bytes, 394 of 436 instructions), the engine keeps all nine. `AssignTextureSlot` (0x1061CBB0)
  **matches** in dxtexture.cpp (AddRef the new, Release the old, store). 0x10623250 `Unknown2` stays EQUIVALENT
  (28.7 %): its unit's `Unknown106229B0` (0x106229B0, the skinning matrices transposed into the vertex shader
  constants from 0x69) compiled before it changes nothing in it. 0x1061C600 `Lock` not reworked (9.7 %).
- (op-eq1) 0x1061D3A0 `CreateDefaultTextures` is EQUIVALENT now (75.3 %, the op-map2 source): the same calls, stores,
  fills and x87 sequences, only the clamp tree differs. The ramp frequencies (0x11276D60 / 0x11276D64 / 0x11276D68)
  and their guard word (0x11276D6C) are function-local statics of the engine and are mapped in symbols.txt with their
  decorated names, so ours and the engine's share them (before the mapping difftest reported the engine's statics
  written and ours not). difftest SAME on the start-up state (70 of 78 engine blocks, 73 with the variants; unreached
  are the allocation failures and the clamps' upper leaves).
- Not reproduced at the merge and marked NONMATCHING: 0x1082DB20 `AddTriggerPackages` (36 %), 0x102D41C0
  `DentBuffer::Push` (26 %, branch layout), 0x102DA540 `LODRenderBehaviour::UpdateFade` (30 %), 0x102DDD30 /
  0x102DDE30 `MidgroundManager::CellLoaded` / `CellUnloaded` (63 % / 62 %).
- 0x107DECD0 `GetHeapKindName` is file-local and its only caller (OnAllocFail 0x107DED20) is not reconstructed, so
  the compiler drops it: NONMATCHING until the caller exists.
- skin.cpp's `BlendRows4` / `BlendRows3` are plain functions, not `__inline`: their only caller (0x1071B9A0) is
  NONMATCHING, and an inline function nothing calls is not emitted.

## Draw slots, stream slots, texture creation, skinning paths, draws (this branch)

Match (100 %): `Mesh::Draw`, `Skin::Draw`, `OnAllocFail` + `GetHeapKindName`, `ShaderPalette` destructors,
`DumpVertexDeclaration`, `LODRenderBehaviour::Update`, `MidgroundManager::CellUnloaded`, `StreamSlotGroup::Create`
(0x1083EC50, streamslotgroup.cpp), both `dxTexture::Create` (0x1061CD70, 0x1061D010), the small `GpuSkin` slots,
`Display::Unknown10616BB0` (the device reset, display.cpp), `dxContext::DrawBatches` (0x10621060) and the small
getters and helpers it brought (`PrimitiveCount` 0x1061F150, `dxVertexBuffer::GetUnknown14`, `dxIndexBuffer::GetUnknown1C`).

EQUIVALENT (the same operations, a different register allocation, schedule or stack slot layout; the compiled body
and the engine's were run on the same random input - their memory, their calls and their arguments agreed
on hundreds of runs): `UpdateFade`, `Slot1` of the LOD behaviour, `CellLoaded`, `Midground Load`,
`AddTriggerPackages`, the `PrimGroupLoader`, `dxIndexBuffer` and `GpuSkin` constructors, `FindVertexDeclaration`,
`dxTexture::Lock` (0x1061C600; the check found that the description's format is `description.format`, not the
device format, which the first version of the body had), `RestoreDefaultPool` (0x10623FB0; its unscaled test is
against 0, the first version of the body tested 1.0), `BlendBoneRows` / `BlendBoneRowsWide` and the eighteen
skinning paths 0x1071B610 - 0x1071E8F0 in skin.cpp (`SkinState::Unknown<address>`: positions, normals, tangents,
the expression's offsets and the wide record's second position, with one or four bones per vertex; the blends are
`BlendRows4Inline` / `BlendRows3Inline` / `BlendBones`), `Display::Unknown106182C0` (the device's creation),
`dxContext::DrawPrimitive` / `Unknown2` / `Unknown10620A20` / `Unknown10620B00`, `UpdateStreamTransition`
(0x1082E100), `StreamDriverBehaviour::Update` (0x10899830) and `Loader1067F4D0::LoadObject` (0x1067F4D0).

Still NONMATCHING or not started, one line each:

- 0x1072B470 / 0x1072B6D0 / 0x1072ADB0 / 0x1072AF80 (DDS loader): the whole-unit compiled helpers take their
  arguments in eax / esi / a stack word. The pixel-format decoder 0x1072A540 is reproduced as a file-local
  function that takes the description in eax (it matches 100 % apart from the jump table relocation), but a
  file-local function nothing calls is not emitted, so it cannot carry an annotation until 0x1072B600 exists.
- 0x10626350 (`dxVertexBuffer::Create`): calls the name to usage helper 0x10625BF0, which takes its name in esi and
  answers in eax / edx.
- 0x104E3840, 0x1041FA40 (start-up tables), 0x1061D3A0 (the default textures), 0x102D4920 / 0x102D4C50 (the deform
  behaviour: they build stack messages whose vftables the unit would have to emit): not started. (The chunk loaders
  0x10B9C3E0 ... 0x10B95780 are in the pure3d/geometry section above.)
- 0x1061D3A0 (`CreateDefaultTextures`, dxdefaulttextures.cpp): NONMATCHING at 36 %. The fills compile to the engine's
  `rep stosd` once the width and pitch are copied into locals before the loop; the register allocation (the zero
  register, the pitch kept in a register) and the order of the description's stores still differ.
- The loaders 0x10B9C3E0, 0x10B90CA0, 0x10B91410, 0x106DE090, 0x10706960, 0x10B96280, 0x10B95780 (large, built on RTTI casts,
  inline string comparisons and bit-field states): not started.
- skin.cpp's eighteen skinning paths (0x1071B610 - 0x1071E8F0) and the two bone-row blenders (0x1071B310, 0x1071B490)
  were EQUIVALENT on the sn-list branch (12 - 26 %, checked only in an emulator with random inputs) and crashed the
  game at start-up (a read of 0xFFFFFFFF in 0x1071B610 called from the skinning task 0x1071EAF0): back to
  NONMATCHING, whole definitions under the ifdef.
- tools/difftest also notes that sequencer.cpp defines `fight::gActiveActions` / `gPeakActiveActions` itself without
  a symbols.txt mapping, so our fight code counts in private copies, not the engine's (to map when their addresses
  are known).

## ravenphysics: physicsobject.cpp, midphasebatcher.cpp, buildcollisioninfolist.cpp, stackallocator.cpp, gjk.cpp, rest of context.cpp (sn-raven2)

- physicsobject.cpp (0x1065F8C0 - 0x10661420): 55 functions, 53 match, 2 EQUIVALENT (`SetBit` 0x1065FB20 and
  `GetPairIndex` 0x1065FC30: register allocation only).
- midphasebatcher.cpp (0x10691690 - 0x10691C30): all match except `Init` 0x10691920 and `QueueBatch` 0x10691AC0
  (EQUIVALENT: instruction scheduling only).
- buildcollisioninfolist.cpp (0x106B2970 - 0x106B2BF0): all match except `InfoRecordArray::Create` 0x106B2A90
  (EQUIVALENT: `jbe` after `test` for `je`) and `MergeRecords` 0x106B2AE0 (NONMATCHING, 10 %: the engine checks the
  counts only behind the copies and leaves through two exits that each run the remaining tails).
- stackallocator.cpp (0x10666F90 - 0x10667250): all match except `ScratchStack::Alloc` 0x10666FE0 (EQUIVALENT:
  operand order of the alignment arithmetic, 85.4 %).
- gjk.cpp: the small functions (0x10672850 - 0x10673750) are done; `CapsuleSupport` 0x10672750 is EQUIVALENT (operand
  order of the dot products), `BoxSupport` is NONMATCHING. The large GJK routines (the solver 0x10673750 on, the
  hull support functions, `GjkDistance` 0x10677180) are declared only.
- context.cpp: the ten `EmptyMembers` functions match, `GetIslandTable` 0x10657F20 / `GetAwakeTable` 0x10657FA0 are
  EQUIVALENT, `IsBodyConnected` 0x106588B0 is NONMATCHING (41.8 %: the engine pushes ebx / ebp / edi only behind the
  early returns and reloads the handle table inside the loop). Not done: 0x10657D00, 0x10659070 and 0x106599C0.
- `ravenphysics::gCollisionObjectTable` (0x1127CAC0) is the one name and class of the handle table; the former
  `PhysicsObjectTable` / `gObjectTable` are gone.

## proto/freeroamevents/eventscripting.cpp (0x1058E3A0 - 0x1058F0A0): 41 functions match

The methods of proto::FREventManager (RTTI; derives engine::DBObserver) that the `fre_` script functions are bound
to, and the Lua C functions that answer questions about the event lists. The registration function (0x1058D180) names
every address (the pairs of a native's name and its address are in the strings it pushes); the closure classes it
builds (Closure0 - Closure3 of FREventManager, in the RTTI) give each method's signature. Layout facts the unit uses:

- The manager: `events` (list of FREvent, next at +4) at +8, `infos` (list of FREventInfo, next at +0) at +0xC,
  a cached event at +0x18, `active` at +0x3C, `unlockedAll` at +0x3D, the package slot pool at +0x40. The global
  is 0x11274F08 (`gFREventManager`).
- FREvent: next +4, medal thresholds from +0x10, name (`core::Name`) at +0x28, flag at +0x9C. FREventInfo: next +0,
  the name text at +4 (seven characters), category +0xC, index +0x10, sub type +0x14, name key +0x18.
- A native that uses `gFREventManager` instead of `this` (AssociateStateMachine) is still a member: the closure
  passes the manager in ecx and the callee pops its arguments. Natives that are registered with RegisterCFunction
  (the `fre_Get...String` family) are plain functions; they have to be non-static here because the registration
  function is not reconstructed (an unused static function is not emitted).
- 0x1058E5F0 (`RemoveUnlockKey`) ends in `ret 4`: a member; the data of the received keys is the game database
  string named by the global 0x1126E4B8.
- Not in this unit's range but needed so the callers keep ecx across the call: 0x1058E3A0 (`IsFreeRoamActive`) and
  0x1058E3B0 are reconstructed too (a caller keeps `this` in ecx across a callee of the same unit that does not
  clobber it).
- Constant arguments that the engine pushes after a call (`lua_pushstring(L, info->GetString(0))`) need the call's
  result in a local first; the engine's `strstr(...)` returned as a bool is `return strstr(keys, key);` (an
  explicit `!= 0` compiles to neg / sbb / neg).

## proto/architecture/pausestate.cpp (0x104E7180 - 0x104E76F0): 19 functions match

proto::GamePauseState (RTTI; PauseState, IRealTimeTask at +0x6C, OLS::Callback at +0x70 with its list node at +0x74,
the borrowed slot group at +0x78 and the state flags 0x7C - 0x90). The unit runs 0x104E6730 - 0x104E7E00; the slot
functions Enter / Leave / Update (0x104E6940, 0x104E6C70, 0x104E6EC0), 0x104E7100 and 0x104E7110 and everything after
0x104E76F0 are not reconstructed (their symbols map to the engine's code, so the vftables our constructor installs
lead to the original functions). What the unit shows:

- A virtual function the derived class overrides only for a second base (IRealTimeTask::Update at 0x6C, the
  callback at 0x70) is compiled with the subobject's `this`: 0x104E6EC0 reads the state at `[this + 0x10]` (= +0x7C of
  the object) and 0x104E7280 sets the byte at `[this + 0x1A]` (= +0x8A). Writing the members of the full object and
  letting the compiler adjust gives the same code.
- The explicit COMDAT copies of inline members that appear in a unit (container::SListLite<OLS::Callback>::PushBack
  and Remove, engine::OLS::AddCallback and RemoveCallback, the Method0 / Closure0 of the class and the RegisterMethod
  instance) are emitted by the compiler once the constructor and the destructor that use them are compiled.
- 0x104E74C0 / 0x104E71D0 borrow and return the memory of the shadow maps as a slot group "PauseBorrowed" (they have
  no callers in the image). The name is built by an inline helper that returns it by value: that puts the Name
  constructor before the argument pushes and the address is loaded with a lea afterwards.
- `Slot2` is called by fe_PauseGame with the id of the first active player (`InputSystem::active.head->id`).

## proto/ai/ambientmanager/behaviours/vehiclebehaviourambient.cpp (0x10446A70 - 0x1044E960): 41 match, 9 EQUIVALENT, 7 NONMATCHING, 6 not started

proto::VehicleBehaviourAmbient (RTTI; VehicleBehaviour : FightTreeBehaviour, container::ListBase::Node at +0x68; vftable
0x10E05340), the ambient traffic car. Of the 63 functions of the range 41 match, 9 are EQUIVALENT (see below), 7 are
NONMATCHING and 6 are not started; the unit also holds 19 neighbours outside the range (the path ring, the speed
update 0x104468F0, the plane tests 0x10446700 / 0x10446890, the stopping distance 0x10445A40 / 0x10445A60, the yaw
rate 0x10445960 ...), which are reconstructed so their callers keep ecx and edx across the call.

Layout facts the unit uses (names are guesses except the reflected ones):

- `VehicleBehaviour`: `extents` (half the size of the car) at +0x78, `halted` at +0x84, the path ring `path88` at +0x88
  (read cursor, write cursor, block, block end; nodes of 0x18 bytes), the byte +0x9C "update again", `unknownA0` /
  `unknownA4` at +0xA0 / +0xA4 (A4 is the start state: 0 free, 2 parked and waiting).
- `VehicleBehaviourAmbient`: wait timer +0xA8, `vehicleProperties` (maxSpeed +0x18, accelerationForce +0x1C, braking
  force +0x20, wheel radius +0x24, damage fields to +0x30) at +0xEC, speed +0xD4, name +0xE0, speed / acceleration /
  braking of this car +0xF0 / +0xF4 / +0xF8, target speed +0xFC, `simulated` +0x100, desired facing +0x104, the facing
  of the car +0x110, physics handle +0x11C, steering angle +0x120, the blocker (game object handle +0x124, point
  +0x128, answer +0x134), the three wheel pairs (spin, steer, two part indices; 0x10 bytes each) from +0x140, the
  "changing lanes" byte +0x170, a random number below three +0x174, mode +0x188 (0 wheeled model, 1 parked,
  2 skidding, 4 dead), the distance to the next node +0x198 / +0x19C.
- `NavArea` (the engine's 0x40-byte navigation records, `gNavMesh->areas`): a plane (normal, offset) at +0x10, a state
  at +0x20 (0, 4, 5, 6, 7 close the area to cars), the list of the cars standing in it at +0x28 and their count at
  +0x38. `unknown74` is the area the car stands in; `NavArea::AddVehicle` / `RemoveVehicle` (0x105680A0 / 0x105680D0)
  take the car's list node (+0x68). `AreaLink::owner` (the index of the object a road segment belongs to) selects
  a handle in `gNavMesh->handles` (+0x28).
- The report-once flags of `VEHICLE_ASSERT_NOT_NAN` are function-local statics of 1 byte, mapped one by one in
  symbols.txt (0x1108CD00 - 0x1108CDD9, descending in the order of the asserts of a function).

What the unit showed about the compiler (each of these decided a function):

- A `math::Vector` local built from the matrix row (`math::Vector p(m[3][0], m[3][1], m[3][2])`) and a second local
  built from arithmetic on it, then copied component by component into the member, gives the engine's loads and
  stores; assigning the member directly or keeping scalars does not (0x104470A0, 0x1044E200, 0x10446A70).
- The length of a difference is `sqrt(d.Dot(d))` (0x104482B0): the compiler then adds the squares in the order z, x, y
  that the engine has; spelling the sum of the squares out lets it pick another order.
- A sign (-1, 0, 1) of a float is `(x < 0.0f) ? -1.0f : ((x > 0.0f) ? 1.0f : 0.0f)` in 0x10446A70 and the if / else
  form in 0x104468F0; the clamp of the steering angle is `(a < max) ? a : max`.
- A temporary of a class with a user-declared copy constructor is constructed in place in the argument (push ecx /
  mov ecx, esp / call constructor): core::BitField<unsigned short> got an inline copy constructor for the nav query
  (0x1044C040); the pure3d code that includes it is unchanged.
- `GetGameObjectEntries()[index]` checks (index, serial, object) in the order of the handle: written out, the three
  tests share one exit (0x1044D200); `GameObjectHandle::Get()` makes three exits.
- The engine's `PathRing::At` is inlined everywhere and `Count` is a call in most functions; 0x1044D730 calls it once
  and has the size written out inline the second time (see below).
- `x - x` is not folded; `-v` loads the -0.0 constant and subtracts.
- A ternary of two handles (`cond ? global : GameObjectHandle()`) selects by pointer; the engine stores the global
  into the temporary, so 0x104485E0 stays EQUIVALENT.

EQUIVALENT (compiled into the DLL in place of the engine's code; none of them has captured states yet, so the
difftest has not run): 0x104473E0 (98 %, push of edi one instruction later), 0x10448440 (54 %, the car lives in a
stack slot), 0x104485E0 (66 %, the handle of the player is selected by pointer), 0x1044AE90 (87 %, stack slots of
the path vectors; the sum of the products is added z, y, x in both), 0x1044B110 (90 %, order of two stores),
0x1044C040 (85 %, registers of the branch and the slot address), 0x1044CEA0 (59 %, esi / edi in the generator
steps), 0x1044D0F0 (70 %, registers), 0x1044D730 (92 %, the engine keeps 1.0 on the x87 stack and compares the
stored distance with an SSE compare where ours compares the x87 value; the value is never within the single's
range of zero) and the neighbour 0x10446700 (87 %). 0x10445A10 is NONMATCHING: ours negates the answer through cl
and so changes ecx, which the engine's copy leaves holding `this`; its caller 0x1044D200 calls 0x10442200 right
after it with that ecx, and the game crashed in free roam.
With /fp:fast the compiler adds a sum of products in the opposite order to the source's: a dot product written
x, y, z comes out z, y, x (0x1044AE90); check that order in the listing before an EQUIVALENT is accepted.

NONMATCHING (inside `#ifdef NONMATCHING`): 0x10447280 (12 %, the engine's frame is 0x18 bytes larger and keeps the zero
in xmm3), 0x10447D20 (52 %, the stack copies of the start point), 0x1044A580 (55 %, the three matrix rows are read
into registers first), 0x1044ABD0 (41 %, ebp / esi allocation and two separate read-modify-write flag updates; the
engine reaches the spin angle as `this + (i + 0x14) * 16` and the part indices as `this + i * 16 + 0x148`),
0x1044B2A0 (56 %, the engine reuses the dead float parameter's slot), 0x1044B480 (55 %) and 0x1044D200 (46 %, the
audio message's destructor is declared out of line in audiomessage.h; the engine has none and shares the tail that
sends the message). The ring size that 0x1044D730 needs is written out by hand (`begin <= end ? end - begin :
(end - array) + (arrayEnd - begin)`); calling `PathRing::Count` there keeps it out of line.

Not started (all are large; what is known): 0x10447740 sets the physics up (the LOD message, the object's bounds
into a box with the identity matrix, the collision object of 0x84 bytes, the handle, the filter 0x8000 / 0x2000, the
random speed, acceleration and brake spread and the wheel parts reset); 0x10448790 casts the rays in front of the
car (the matrix rows copied as 16 words, the OBB sweep through 0x100F7C40 and the nearest other car by a loop over the
physics bodies; it fills the blocker fields +0x124 - +0x138 and the distance at +0x180); 0x104490F0 is the damage
routine (two bodies, the impulse along the contact normal scaled by the car's damage factor, a message to each body
and the deformation message); 0x10449680 sets the car on the ground (the height and the up direction from the
physics world, 3062 bytes); 0x1044C340 executes a lane change (the neighbour lanes from 0x10448FC0, the path nodes
rebuilt around the new lane, 2322 bytes); 0x1044DB60 is the
collision handler (the contact, the damage routine, the horn and the state change to mode 3).

## mp-game session (2026-10-18): matching with the engine's own containers

What solved the two functions below: the engine's inline code works on the container classes (`ArrayDynamicHeap<T>` and
the dent buffer, an `ArrayFixed`-shaped array), through `IsEmpty()`, `Size()` and `operator[]`; the earlier sources used
the same members as raw pointers and compiled to the same instructions with other registers. The register choices of
VS2005 depend on the inline functions' parameters (an inlined member keeps its `this`), so the container methods and the
access path (through the array object or through the owner) are part of the source.

- 0x102DC5F0 `LODRenderBehaviour::Slot1` **matches**. `ready` (+0x40) and `levels` (+0x50) are
  `container::ArrayDynamicHeap<LODReady>` / `<LODLevel>` (begin, end, capacity and the heap word; the old header had them
  as pointer pairs with unknown words between). The tests are `!ready.IsEmpty() && !levels.IsEmpty()`, the first ready
  record is `ready[0]`, the loops run to `ready.Size()` / `levels.Size()`, and `distanceLevel = 0` comes after the half
  diagonal (so the zero shares eax with the loop counter). `UpdateFade`, `UpdateLevel` and `Update` keep matching.
- 0x102D4C50 `DeformShaderModifier::Apply` **matches**: the emptiness test and the loop bound go through `dents.IsEmpty()`
  / `dents.Size()` and the elements are read as `dents.dents[i]`; the old source reached all three through a local
  `DentBuffer* buffer = &dents;`, which the compiler folded into the modifier's base register and CSE'd the end pointer.
- 0x1041FA40 `AmbientManager::AmbientManager` stays EQUIVALENT but at **98.0 %** (was 28.9 %): the fixed pools
  (+0x270, +0x540, +0x5DC, +0x5EC) now carry a `container::AllocatorCoreAligned<16>` as their fourth word and allocate
  with `allocator.Alloc(count * sizeof(T))`; the heap then reaches the call as a member read (`mov eax, esi`) and the
  whole body's register choices fall into the engine's. What is left is the scheduler's place for the `push 1` of the
  empty name (`Name("", 1)`): the engine pushes it between the stores of members +0x604 and +0x608, we right after
  `or esi, -1`. Moving members into the body, the name block, the name as a temporary: no effect.
- (op-map1) 0x1041FA40 `AmbientManager::AmbientManager` **matches**: the member at +0x604 is an object whose own inline
  constructor sets it to -1 (`AmbientIndex`, a guess); the member object's constructor puts the push of the empty name's
  flag right after its store, as in the engine. Wrapping any other run of the last members does not.
- 0x1082E100 `UpdateStreamTransition` stays EQUIVALENT, **84.9 %** byte-wise (was 21.1 %): the two lists are
  `container::ArrayDynamic` locals made with `Create(16)` after their declaration (the declaration order and the way
  they are made decide which of them lies lower in the frame), the counts are `Size()` and every size test is `> 0` /
  `<= 0` (VS2005 keeps the flags of the shift for those; `!= 0` and `== 0` become `test reg, -4`), the unload loop
  removes a package with a Find that caches the end and a shift that reuses it (a Find followed by an Erase that reads
  the end again reloads it), and the group of the first package is searched in `*current` and then `*target`. Left:
  the engine holds the dropped count in esi and the package in edi (ours the other way round, in the whole loop),
  the known array's begin in edx and its first package in eax, and copies the end of the list into edx / esi after the
  search (ours reuses one register or reloads); one alignment byte.
- (op-map1) 0x1082E100 stays EQUIVALENT, now 94.5 % (was 84.9): `EraseElement` reads the end before it steps past the
  position (the engine's copy of the end into another register after the search) and the group search takes the first
  package into a local. `EraseElement(*current, FindElement(*current, package))` in the unload loop (instead of
  `RemoveElement`) gives the engine's registers there (count esi, package edi, the end copied), but then the zero of
  the group and of the loop counter stop being shared (`mov ebp, 0` between `sar` and `je`) and the search loop is
  aligned with a jump over the padding (762 bytes). difftest SAME (9 states).
- (op-map2) 0x1082E100 stays EQUIVALENT (94.5 %): which of the two states comes out follows whether the unload loop's
  search reads the list's end in its condition (FindElement: the engine's registers, no shared zero) or caches it in a
  local first (RemoveElement: the shared zero, swapped registers); no other spelling of the search (for / while forms,
  a break, an index) gives both. Declaring the loop counter before the group search restores the shared zero with
  Find + Erase but moves the pushes of ebx / ebp / esi behind the first two loops (56 %).
- (op-map3) 0x1082E100 stays EQUIVALENT (94.5 %): a barrier after any statement of either form, an inline wrapper around
  Find + Erase, the counter declared outside the loop and the orders of the lists' set-up statements change nothing;
  the group pointer declared ahead of the two loops gives the Find + Erase form its shared zero but one more frame
  slot (77 %).
- (op-map4) 0x1082E100 stays EQUIVALENT (94.5 %): with Find + Erase in the unload loop the list taken into a local
  first (`list = *current`) gives the engine's size (753 bytes) but drops the copy of the end, one counter shared by
  the three loops, the group set in an else branch, a while form and the dropped count computed before the group
  search do not bring the shared zero back; its two forms still each give one half.
- 0x1082DB20 `AddTriggerPackages` **matches**: the centre of the trigger's box is an inline member of the box (the engine
  computes it the same way in five places: this function, `CollectPackages` 0x1082D0B0 and the functions at 0x108EB920 /
  0x108EBC80), `centre->Add(min, max); centre->Scale(0.5f)`. Inside the member the three sums come out with the
  engine's operand order (min.x + max.x, but max.y + min.y and max.z + min.z); the same call written on the trigger's
  box from outside, a hand-written `(min.x + max.x) * 0.5f` per axis, or a free function taking the box, loads the
  higher offset first in all three. The method is `StreamTriggerBox::GetCentre` (streamtrigger.h, a `math::AABB`
  with the member); it is not in `math::AABB` itself because any new name in that class moves the stack slots of
  `pure3d::Context::LoadDebugFont` (0x1070FC90) and that function drops from 100 % to 98.7 %.
- 0x102DDD30 `MidgroundManager::CellLoaded` **matches**. Three facts, found one after the other: (1) the engine copies
  the record with loads of all three members before the stores into the array (`mov ecx / mov edx / movss xmm0`, then
  three stores); VS2005 only reorders those loads above the stores when the destination pointer is a **local
  `__restrict` pointer in the same function** (a pointer loaded from a member, a parameter of an inline function, a
  restrict member or parameter, `/Oa` and `/Ow` all keep the load-store pairs), so the body of `PushBack` is written
  out with `MidgroundCellRecord* __restrict item = records.end++`; (2) the compiler-made copy then needs the record's
  copy constructor inline in a body that already has calls, which only `__forceinline` gets (the member-wise copy is
  written as an initialiser list, the order name, drawable, unknownC, unknown10); (3) the record has to live in a block
  of its own after the two calls (`if (drawable != 0) { calls; { record ... } }`), because a local declared after
  calls in the same block gets its own 0x18 frame bytes instead of the iterator's, and the frame is 0x38 instead of
  0x20. The record's eight-byte alignment is a trailing `unsigned __int64 align8[0]` (it adds no bytes and does not
  realign the stack; the earlier `int padding14` made the copies move it).

## Open: callee-saved push in the entry block before an early exit (2026-10-20)

In 583 engine functions (almost all `RegisterProperties`-style: `sub esp, 0x400; cmp [guard], 0; push esi; jne exit`)
the engine saves the callee-saved register in the entry block and the early exit jumps to the full epilogue
(`pop esi; add esp, N; ret`); in 44 others it sinks the push behind the branch as VS2005 SP1 does for us. Ours always
sinks it (`jne` to `add esp, N; ret`, the push after the branch) unless a value live at entry (`this`, a register
argument) must be moved into the callee-saved register before the branch (`push edi; mov edi, ecx; jne`).
Tried without effect on 0x10807B50 (all 98.1 %): early return, positive `if` around the body, `do { break; } while`,
`goto`, the pointer or the array declared before the guard, the guard through a pointer, an inline guard, the body in
an inline helper, a template static member; flags /Ob0 /Ob2 /Ot /Os /O1 /Ox /Oy- /GS /Gs0 /GF /Gd /arch:SSE2
/fp:precise /EHsc /Zi /Oi /Oi- /GR- /MT, /Gy off; /GL with /LTCG; `#pragma optimize` g / t / y / s. The other functions
of the same units match, so it is not another compiler for those units. Still open.

## Open: which class is dxContext (2026-10-20)

`pure3d::Context::~Context` (0x107106A0) deletes the object at 0x1127F358 (`gPddiDx`, declared `dxContext*`) through
0x1070EDD0, whose destructor is 0x1061BEC0; sn-d took 0x1061BEC0 / 0x1070EDD0 for the driver object `dxDevice` (made by
0x1061BBC0, kept at 0x11276D40) and named the real dxContext destructor 0x10622A50 (deleting form 0x10623650, vftable
slot 66, constructor 0x1061F410). Moving the two names to dxDevice breaks ~Context (89.8 %), so the object behind
gPddiDx and the classes the tree calls dxContext / dxDevice have to be sorted out together, with the dxContext
constructor and its 69-slot vftable.

## fight system, supporting surface, effect actions, the effect manager and the effect LOD records (0x10800000 - 0x10820000, sn-e)

Sources: `engine/fight/fightsystem.cpp` (start-up, shutdown and the context initialisers), `supportingsurface.cpp`
(the SupportingSurface / SupportingLimb conditions), `effecttrack.cpp` (`EffectTrack::CreateAction`, the motion trail
action's start), `engine/render/effectmanager.cpp` (the global effect manager at 0x1130CCE0: lights, the hash tables of
playing effects and attached drawables, stores, starting and updating effects, motion trails) and
`engine/render/effectlod.cpp` (RTTI engine::EffectLOD and its three kinds, base NonCopyable).

NONMATCHING (bodies under `#ifdef NONMATCHING`):

| Address | Function | Best | Note |
| --- | --- | --- | --- |
| 0x10809DA0 | SupportingSurfaceVelocityAngleCondition::Evaluate | 36.0 % | arithmetic right; scheduling and the constant folding of the angle test differ (1.0f / 0.5f stay memory operands in the engine) |
| 0x1080A170 | SupportingSurfaceDistanceCondition::Evaluate | 64.7 % | the engine adds the dot products z, y, x (position z with normal z first); `Vector::Dot`, explicit z-y-x sums and a permutation search over the nine reorderable spots all stay at 55 - 65 %, the loads are scheduled differently |
| 0x1080A290 | SupportingSurfaceTimeToImpactCondition::Evaluate | 41.9 % | the engine builds the two velocity vectors on the stack before it reads the surface and schedules the dot products later |
| 0x1081C260 | EffectManager::UpdateAttachedTransforms | 25.7 % | the same walk and calls; the engine hoists the load of the master table out of the loop and reloads it after the queued call, ours loads it inside the validity checks of every ring entry |
| 0x1081BCE0 | EffectManager::UpdateLights | 24.8 % | the same calls and branches; (1) the matrix copy is a four-times loop (`fld / fstp` x4, the destination reached as source plus a constant) in the engine, ours unrolls it however the loop is written; (2) the colour blend is scheduled as three passes over four channels (loads first, then the subtractions, multiplications and additions); (3) the decay range multiplies 0.5 into the wave before the amplitude; (4) the destroy test keeps `expired \| lost \| inactive` as values |

`AbortEffectTrack::GetSlotIndex` 0x10804EE0 and `EffectSpawnTransform::BuildMatrix` 0x10805750 (effecttrack.cpp, earlier work in this range) stay NONMATCHING;
`EffectLODSwitch::GetEffect` 0x1081EAA0 has the same register swap as `GetSlotIndex` (an out pointer written from a member).

EQUIVALENT (compiled into the hybrid DLL, not counted; the percentage is the best one reached):

- fight: the eight SupportingSurface `RegisterProperties` (the shrink-wrapped esi push), `DrawRandom` 0x10811ED0 (19 %),
  `StartFightSystem` 0x10812610 (97 %), `MotionTrailAction::Slot5` 0x10805D30 (16.7 %).
- effect manager lights and lookups: `ClearLightReferences` 0x1081A000 (82.4 %), `SetEffectSpan` 0x1081B5D0 (87 %),
  `SetEffectPosition` 0x1081B970 (82.3 %), `ReleaseAttached` 0x1081B9B0 (78.5 %), `CreateMotionTrail` 0x1081BA90 (34.5 %;
  the engine reuses dead parameter slots for its locals).
- hash tables: `HashLookup::FindForInsert` 0x1081A910 (71.1 %), `HashLookup::Next` 0x10819C30 (16.8 %),
  `HashTable::Insert` 0x1081C620 (51.7 %), `HashTable` constructor 0x1081D170 (51.5 %).
- effects: `Reset` 0x1081C8D0 (39.3 %; the engine reads the waiting ring's tail into a spare slot nothing uses),
  `ReleaseStore` 0x1081CDE0 (47.4 %), `RemoveInstance` 0x1081D790 (57.7 %), `RemoveOldest` 0x1081D850 (22.4 %),
  `RemoveOldestStore` 0x1081DA10 (13.6 %), `UpdateInstances` 0x1081D540 (52.2 %), `CreateAttached` 0x1081CBB0 (37.5 %),
  `CreateSpanEffect` 0x1081CE70 (58 %), `CreateEffectFromStore` 0x1081DAF0 (19.1 %), `AddInstance` 0x1081DC30 (38.4 %),
  `CreateEffect` 0x1081E390 (43.9 %), `StartEffect` 0x1081E6B0 (42 %), `EffectInstance::SetEmitting` 0x1081EB10 (24.8 %),
  `EffectInstance::StartFade` 0x1081EEF0 (38.7 %), `EffectLODBias::Blend` 0x1081F070 (87.3 %).

Lessons: (1) a 64-bit shift of a zero-extended 32-bit key (`unsigned __int64 wide = *key; (unsigned int)(wide >> 9)`)
keeps the `shrd` the engine has, where `(unsigned __int64)*key >> 9` is narrowed; (2) `Value* result = cond ? 0 : x; return
result;` as the last line of an inlined step keeps the join of the two paths the engine has; (3) a named local
`EffectName key(...)` instead of a temporary removes the temporary's destructor flag; (4) the 4-byte dead load and spare
frame slot in `Reset` come from an inline expansion that cannot be written down plainly (a `volatile` local gives 77 %).
(5) The engine's `HashLookup` and the later `InstanceOptions` share one stack slot (frame 0x28 instead of 0x3c in
`CreateEffect`); the compiler does that when the options object lives in an inner block and the lookup is a temporary or
the local of an inlined helper (`EffectManager::GetList`).

Not started: `BeginEffect` 0x108060F0 (5153 bytes), the effect manager's constructor 0x1081DE50 and destructor
0x1081D1E0 (inline container construction from a configuration record), the named-timer table functions 0x1081D080 /
0x1081DCF0 / 0x1081E460 (they use another unit's name table), 0x1081C360 (a callback that calls a method at 0x10821420
of the playing effect, in the next unit), the effect instance's own functions from 0x10820000 on (sn-f's range) and the
small container template instances between 0x10819520 and 0x10819FD0 and in 0x1081A200 - 0x1081C3FF (vector, ring and
allocator members of the manager's record types; the classes are the engine's own and unnamed). `math::Noise::Evaluate`
is mapped at 0x101043F0 (called through the jump at 0x100037F1); the math worklist reconstructs it.

## render/async/private/shaderparameter.cpp (0x10826970 - 0x10829D70, partly): the shader parameter calls, events and interpolators

Done: the `SetParameter` / `InterpolateParameter` / `SetParameterEnabled` calls of the game thread, the
`StructRenderEvent<ParameterReference<T>>` instances (constructor, `Execute`, the `Begin` template), the `Apply*` /
`Start*` functions of the render thread, the interpolator constructors and `Update` for the six types, and the seven
`QueueObjRenderEvent` instances of the canvas unit.

- `Ease` (0x10827980) is EQUIVALENT (86.8 %): the clamp block is laid out differently; `LerpVector<Vector>` (0x10827EC0),
  `LerpVector<Vector4>` (0x10827F30) and `Update` of the vector interpolators (0x10828C70, 0x10828D60) are EQUIVALENT
  (instruction scheduling of the vector copies).
- `BlendColours` (0x10827FD0) is NONMATCHING (19 %): the engine keeps its temporary colours in dead argument slots.
- Not started: the Display subsystem (the `HandleTable<DisplayData>`, `DisplayInfo`, the 619-byte display create at
  0x10829750, 0x10829DE0, 0x10829ED0, 0x10828120, 0x10828230 and the `RenderEvent1/2<Display>` instances), the unused
  `RenderContext::SetParameter<T>` instances at 0x10826970 - 0x10826CE0, the `ParameterReference` constructors and
  destructors, the scalar deleting destructors, the one-byte `ret` copies and the naked atomic helpers 0x10826780 /
  0x10826790.

## system/gamestate.cpp (0x108366C0 - 0x108391C0): the game state machine

Done: the simulation driver (`ISimulationDriver`), the game state table with its states, requests, tasks and request
names, the request list and the per-frame functions of the machine. The vector template of the table is local to the
unit (`StateVector<T>`).

- EQUIVALENT: `SetSimulationDriver`, `AddStateFlags`, `RemoveStateFlags`, `GetRequestName`, `GetGameStateStatus`,
  `IsGameStateOnTop`, `HasPendingStateChange`, `IsStateMachineBusy`, `FreeGameState`, `AddRealTimeTask`,
  `AddSimulationTask`, `RunStateFiber`, `CancelStateRequest`, `RequestGameStateByIndex`, `GameStateRequest::OnFinished`
  (registers and the order of the loads of small functions).
- NONMATCHING: `StartNextRequest` (63 %), `RemoveGameStateFromStack` (34 %), `GotoGameState` (25 %),
  `RequestGameStateInternal` (33 %): the engine's loops over the request list and the stack differ in shape.
- Not started: 0x10837D00 (1299 bytes), 0x10838BA0 (781 bytes) and 0x10838ED0 (541 bytes).

## fmv/fmvplayer.cpp (0x1082EC10 - 0x1082FA00): the full-motion video player

Done: the request queue (a doubly linked list whose linking functions live at 0x1060E6C0 - 0x1060E900 and are shared
with other lists), the state functions, the Lua calls `fmv_Skip` / `fmv_Stop` / `fmv_IsPlaying` / `fmv_IsLoaded`, the
channel map and the list template's inline members. The decoder (0x1059F000 - 0x105A1000) is only called.

- `UpdateMovies` (0x1082F300) and `UpdateMovieState` (0x1082F7A0) are EQUIVALENT: the engine keeps the decoder pointer in
  `ecx` through the creation of the decoder, loads the `this` of some calls after their arguments and pops the first
  list node through `eax`. `goto` in the source of `UpdateMovieState` stops the compiler from sharing the constants 3
  and 9 in registers; the chain of `else if` gives the engine's code.
- Not done: the default constructor of a request (0x1082EC40, 82 bytes; no user in the unit), the iterator / allocator
  helpers 0x1082F170 (a forwarder to `LuaScriptManager::RemoveFunction`), 0x1082F5A0, 0x1082F5B0, 0x1082F670, and the
  empty functions / jump thunks 0x1082F000, 0x1082F010, 0x1082F180.
- Findings: a name that is passed on has to be a named local (`Name name(text, 1); Foo(name);`) where the engine takes
  its address again; a temporary reuses the constructor's returned `this`.

## scenario/scenariolisters.cpp (0x1082FAD0 - 0x10832330): the editor's lists of scenario messages and handle names

Done: `ScenarioMessageLister` and `AffiliateLister` (RTTI names, `fight::ListObject` with three pure slots), their
fixed arrays, the eleven `RegisterMessageKind<Message>` instances, the `GetHandleInfo` statics of the message classes,
the `std::sort` instances for the two entry types (`_Push_heap`, `_Median`, `_Adjust_heap`, `_Pop_heap`, `_Make_heap`,
`_Insertion_sort`, `_Sort`, the `copy_backward` family) and `SortListers` / `ResetListers`.

- EQUIVALENT (same calls and stores in the same order, other registers and spills): `_Med3`, `_Unguarded_partition`,
  `_Insertion_sort1`, `_Pop_heap_0`, `_Sort_heap` for both entry types.
- NONMATCHING: both `Add` (95 % of the instructions: the engine clears the first word of the temporary name before its
  constructor runs).
- `std::sort` has to be called out of line, as the engine does: `void (*sorter)(Entry*, Entry*) = std::sort<Entry*>;
  sorter(first, last);` (a plain call is expanded; the same form is used in the tag set). The engine keeps two copies
  of the function per type, the first without a caller (0x10832250, 0x10832270); only the second (0x10832290,
  0x108322B0) is reproduced.
- The entry types have to be 16 bytes without `__declspec(align(8))` on the name (an aligned member makes a by-value
  parameter of the algorithms illegal and changes which helpers the compiler inlines): a trailing `int padding` and
  member-wise copy functions that leave it out give the engine's code. The order of the explicit instantiations
  decides which helpers are inlined into the next one; the `Sort` members have to come before them.

## system/tagset.cpp (0x108340A0 - 0x10835190): the tag set

Done: `TagSet` (a sorted array of names and the "all" flag): the constructor, `Clear`, `Find`, `Contains`, `Intersects`,
`Includes`, `Add` with its sorted insert, `Remove`, `Sort`, `ToString` (with its function-local text, 0x1130DC68) and
`FromString`, and the `std` sort instances for `core::Name<CaseSensitiveKey>*` (`_Med3`, `_Push_heap`, `_Median`,
`_Adjust_heap`, `_Pop_heap`, `_Make_heap`, `_Unguarded_partition`, `_Insertion_sort`, `_Sort_heap`, `_Sort`) plus the
lower-bound function the unit has of its own (a plain function template, not `std::lower_bound`).

- EQUIVALENT: `Intersects`, `Includes`, `Add`, `Remove` (register roles and the order of the first loads) and the sorted
  insert 0x10834D70 (register choices and the layout of the search loop).
- Not done: 0x108340A0 (a forwarder that compares a string with a literal, no user in the unit), 0x108340D0, the
  jump thunk 0x10834750 and the first copy of `std::sort<Name*>` (0x10834FC0, no caller).
- The copy of the array's `ShiftUp` the insert calls is another unit's (0x102EB9A0); it is declared as a specialisation
  without a body so the call stays external.

## ravenphysics 0x10660000 - 0x10680000: start-up, the collision volumes and their neighbours (sn-k)

- `src/code/ravenphysics/src/physics.cpp` (0x10661950 - 0x10661BB0): the scratch stack's counters, `InitSettings`, `Init`,
  `Shutdown` and `GetStatistics`. The library's start-up calls a dozen functions of other units, declared as
  `Unknown<address>` in the file. All match.
- `src/code/engine/motionvelocity.cpp` (0x10661CB0 - 0x106628D0): the velocity helpers of the motion tracking filters
  (`ComputeLinearVelocity`, `ComputeAngularVelocity`, `ComputeVelocities` and a copy of the rotation delta helper).
  EQUIVALENT: the flag registers (88 % / 86 %) and the shrink-wrap of `ComputeVelocities` (72 %).
- `src/code/ravenphysics/collision/src/collisionvolume.cpp` (0x10663E30 -): the volume head and the capsule (type 0), box
  (1), sphere (2) and plane (5) volumes. The type byte is 0 capsule, 1 box, 2 sphere, 3 convex hull, 4 cylinder,
  5 plane, 6 mesh (`GetTypeName`'s table); the per-type methods of the former `CollisionVolume::SetCapsule` /
  `SetSphere` / `SetVolume2` / `SetVolume4` moved to `CollisionCapsule` / `CollisionOBB` / `CollisionPlane` /
  `CollisionSphere` (the old names set the wrong type: 0x10665060 sets a box, 0x10665510 a sphere), and
  `CollisionObject::SetSphereVolume` / `SetVolume2` / `SetVolume4` became `SetOBBVolume` / `SetPlaneVolume` /
  `SetSphereVolume`. `CollisionVolume::bounds` is a `math::AABB` now (was two vectors). `CollisionVolume::SetQuery` and
  `CollisionObject::SetVolumeQuery` scale the volumes by a vector (the argument is not a query).
  - EQUIVALENT: `SetCapsule` 0x10664BA0, `SetSphere` 0x10665510 (the engine addresses the fields from this + 4),
    `Scale` of the sphere 0x10664530 and of the box 0x106642E0, `GetLocalOBB` 0x10664220 (loads in registers).
  - NONMATCHING: `CollisionCapsule::UpdateWorld` 0x10664C10 (15 %: the engine builds the extents in a stack vector and
    takes the absolute values one at a time on the x87 unit).
  - The volume dispatchers (`GetTypeName`, `Print`, `UpdateBounds`, the scale `SetQuery`, `Clone`, `CastVolume`, the
    filter setters), the mesh volume (type 6: `CollisionVolume6` with its `BroadPhaseGrid` at +0x30, 0xF0 bytes, and
    the `MeshSlot` the copies share), the cylinder's copy constructor and the unit's `std` instances for
    `unsigned short` (the sort chain of a list of face numbers) match. The case labels of a switch decide the table's
    size (`SetQuery` has an empty `Scale` for the hull and the mesh), and their order the order of the code.
    `PrintMesh` (0x10665DA0, an empty function) sits in `collisionmesh.cpp` so that the compiler does not see its
    body (the engine keeps the call).
  - EQUIVALENT: the grid constructor 0x106662C0 (scheduling, 85.8 %), `CollisionVolume6::UpdateWorld` 0x10665E20 and
    `MultiplyWorld` 0x10666000 (the engine reuses two stack slots for the row copies, 89.5 %).
  - Not done here: `CollisionCapsule::Scale` 0x10664EB0 and `CollisionOBB::UpdateWorld` 0x10665120 (long SSE
    sequences, declared only), the cylinder's and the hull's other methods (0x1068....).
- `src/code/ravenphysics/constraints/` (new; 0x106615E0 - 0x1066AF80): the `Constraint` base (`constraint.h`, constructor
  0x1065E3E0, destructor 0x1065CD80) and its first two families, `ConstraintInsideOfSphere` (pointA 0x24, pointB 0x30,
  sphereRadius 0x3C) and `ConstraintInsideOfCone` (axisA 0x24, axisALocal 0x30, axisB 0x3C, sine 0x48, cosine 0x4C, flag
  0x58): constructors, the accessors, `Rotate`, `GetMembers` and the reflection templates. Vector members that are reached
  through a getter and a setter use the new `src/code/content/vectormetatype.h` (`VectorMetaTypeGetSet`,
  `VectorMemberGetSetter<C>`); the base `VectorMetaType` slots 0 - 11 are mapped in symbols.txt. A derived destructor is
  left implicit (the engine's is a bare `jmp` to the base destructor); the engine's addresses sit on the stacked
  annotations of the kept copies.
  - EQUIVALENT: `Constraint::Constraint(int)` 0x1065E3E0 (register choice), `ConstraintInsideOfSphere::ScaleBy`
    0x106616E0 (scheduling).
  - Not done: the other constraint classes (hinge 0x1066B0A0, springs, slider, perpendicular axes, fixed distance).
- `src/code/ravenphysics/constraints/src/hinge.cpp` (0x1065B9A0 - 0x1065C2B0 and 0x1066B0A0 - 0x1066B570):
  `ConstraintBallInSocket` (pointA 0x24, pointALocal 0x30, pointB 0x3C, flag 0x60), `ConstraintAlign2Axes` (axisA 0x24,
  axisALocal 0x30, axisB 0x3C, perpendicular 0x48, cross 0x54) and `ConstraintHinge`, which holds one of each at +0x24
  and +0x88 and adds vftable slots 8 and 9 (`SetFirstObject` / `SetSecondObject`). All match except
  `ConstraintBallInSocket::ScaleBy` 0x1065BB90 (EQUIVALENT, 15.8 %: the engine multiplies a freshly loaded stored
  component by the held scale component). `content::GetClassMetaType<Constraint>` is mapped to the engine's copy
  (0x1065BC40). The rest of the constraint classes (angular spring and velocity with their shared properties, slider,
  spring along axis, perpendicular axes, fixed distance, ...) and the base class functions 0x1065E430 - 0x1065EEE0
  (constructor between two objects, copy constructor, `SetObject`) are not done.

## 0x10920000 - 0x10940000 (fight actions and conditions, behaviours, driving attributes, socket layer)

Of the 1492 functions of the range 11 (the crypto module) were matched before this pass; afterwards 276 are (the
pass also maps the template instances the new units keep). The new sources:

- `src/code/engine/fight/` physicsblend, onlineconditions, inputconditions, ragdoll, supportinglimb / supportingstick,
  characterik, rootcontrol (accessors and `Evaluate` of the tracks and conditions) and the new action files
  physicsblendactions, ragdollactions, supportinglimbactions, characterikactions, rootcontrolactions
  (`fight::Action` ctor / dtor / `Slot5` / `Slot6` / `Slot7` and the tracks' `CreateAction`), with the messages in
  `physics/ragdollmessages.h`, `physics/supportinglimbmessages.h`, `physics/physicsmessages.h` and the driver-reference
  templates in `fight/driverrefs.h`.
- `src/code/engine/fight/behaviours/proplogictreebehaviour.*` (all 7 functions of the unit match except
  `OnMessage` 0x10921800 and the 475-byte method 0x10921620, not done).
- `src/code/engine/driving/`: vehicleattributes (VehicleMassAttributes), boundedgraphs (the four bounded graph
  attribute classes and the graph helpers), carattributes (CarSuspensionAttributes, CarControlAttributes,
  HelicopterControlAttributes), graphknots (`GraphKnots::SetKnot`), vehicleintentionbehaviour. Members reached through
  a getter and a setter use `content::GetMemberMetaType<C, T, Id>`, the new overload with an Id (one instance per
  member, as the primitive meta types).
- `src/code/engine/system/networksockets.cpp`: the Winsock layer (handles, bind / connect / send / receive,
  asynchronous host lookup, options, startup / cleanup). The unit was compiled without `/arch` (`// CFLAGS: !/arch`:
  with it the compiler turns a two-way maximum into a `cmov`). The toolchain has no SDK headers, so the Winsock and
  Win32 calls are declared in the file; the engine imports them by name and link.exe looks for the decorated stdcall
  name, so each declaration has an `/alternatename` pragma to the plain `__imp__name`.

Compiler facts found on the way:

- `if (!(x > lo)) x = lo;` is the clamp the engine uses for a minimum (it does not become a conditional move and keeps
  the compare direction); `x <= lo` or a ternary does not.
- The register-passing "custom" calling convention appears for a file-local `static` helper called only from its own
  unit (the socket layer's handle lookup, error mapping, address converters all match as statics). An inline helper
  defined in a header is only kept out of line when the engine kept it.
- Unused `static` functions are not emitted at all; a kept copy of a header function needs a call the compiler does
  not inline (`/Ob1`: only functions defined in the class body or marked `inline` are inlined).
- A caller reloads `ecx` after a call of a function in another unit (or one that calls one) and not after a leaf
  function of its own unit; `GraphKnots::SetKnot` therefore lives in its own file.
- `extern const float` objects (the pooled constants 0.5, 0.3, 30.0, ... `gHalf` / `gPointThree` / `gThirty`) are loaded
  from memory at every use; a literal is loaded once and kept on the x87 stack across calls.
- A `switch` whose cases all end in the same call is compiled with the call duplicated per case when the source has
  one call per case (socket options); a shared `goto` for the failure return gives the engine's single exit.

EQUIVALENT (no difftest states exist for any address of the range):
- shrink-wrap push placement: 0x1092D4B0, 0x1092D610, 0x1092EB30, 0x109302D0, 0x1092EFD0 (also register choice).
- register allocation / stack slots: 0x1092CF50, 0x1092D830, 0x1092D960, 0x1092E780, 0x109304D0, 0x10934910 (the gap
  constant in xmm2 against xmm1).
- scheduling / instruction selection: 0x1092F1E0, 0x1092FB00, 0x1092FB90, 0x10935470 (the first setter's argument is
  loaded before the two curve stores), 0x1093E9B0, 0x1093F100, 0x1093F1A0, 0x1093F710 (the order of two address loads).

NONMATCHING (bodies under `#ifdef NONMATCHING`):
- `0x1093D2D0` / `0x1093D330` / `0x1093D3D0` / `0x1093D440` (the graph helpers `NormalizeBounded`,
  `NormalizeBoundedSigned`, `MoveTowardsBound`, `InterpolateGraph`; 15 - 38 %): the engine takes `fabs` on the x87
  stack, stores the result back into the argument and then does the arithmetic in SSE, ours stays on the x87 stack.
  `InterpolateGraph` also calls the math module's clamp through its jump (`ClampFloat`, mapped to 0x10069040).
- `0x10931C30` (`ReadStrafeInput`, 54 %) and `0x109332B0` (`StrafeAdjustRootAction::Slot7`, 69 %): the helper takes
  the object in ecx and the result pointer on the stack.
- `0x1093EB30` (`Poll`, 40 %): the engine pushes all four registers at the entry and puts the return of 0 right behind
  the first loop; the loops and the set updates are the engine's.

Not done in the range: the NIS player behaviour (0x109201C0 - 0x10920900, calls into the NIS system of 0x1091F...),
PoseAnimation, Physics (0x10921A10 - 0x10924A70), Ragdoll and RagdollLOD (0x10925050 - 0x10927D20),
SecondaryPhysics (0x10927F60 - 0x10929570 and the joint driver 0x10937750), Tag, Touch, TrackedMotionToExpression
(0x10929670 - 0x1092B520; they need the trigger volumes, the pose expression library and the container classes of
other ranges), `TurnInputCondition::Evaluate` 0x1092DAA0, the remaining fight `Slot5` / `Slot7` of the
tracks whose actions sit beside the ones above, the car and vehicle physics attribute classes and behaviours
(0x10935CF0 - 0x10936B40 are inline methods of the car physics attributes, whose class sits outside the range),
`WheelData` (needs a string meta type), the audio emitter / zone behaviours (0x1093B7E0 - 0x1093CE00), the socket
layer's `GetLocalNetworkInfo` 0x1093F920 and the small `0x1093FD20` helper, and the controller input log manager
(0x109337A0 - 0x10933E00).
## 0x108FF310 - 0x10920000 (sn-o): the scenario condition properties, the reflected content classes

- `src/code/engine/scenario/scenarioeventconditions.cpp` (0x108FF310 - 0x10900260, the tail of the previous range's
  last unit): the constructors, destructors, property setters, property lists and factories of
  `ScenarioMessageCondition`, `ScenarioGameObjectAttributeCondition`, `ScenarioGameObjectTouchesTriggerCondition`,
  `ScenarioPropStateCondition` and `ScenarioStringCondition` (their evaluations are in scenarioconditions.cpp), plus the
  property and factory template instances. 95 functions match, the five `RegisterProperties` are EQUIVALENT (the
  open shrink-wrap question; the touch-trigger one also stores its table count before the vftable). The properties
  settled the names of the touch condition's two names: "gameObjectName" is the word at +0x10 (`object`) and
  "triggerName" the one at +0x18 (`trigger`); the getters 0x108C15E0 / 0x108C15F0 and the evaluation in
  scenarioconditions.cpp were renamed to follow. The object is 0x28 bytes (a word at +0x24 nobody writes).
- `src/code/engine/camera/cameraloader.cpp` (0x109067F0 - 0x10906B20): `engine::camera::CameraLoader` (camera object at
  +8, avatarName +0x10, cinematographerName +0x18, spawnActive +0x20, type +0x24 of the enumeration
  `engine::camera::CinematographerType`). `Camera` gained its two reflection statics (0x1084D830 / 0x1084DCC0, another
  unit). The constructor is EQUIVALENT (the lea of the first name member sits behind the reference count store in
  the engine). Not done: the load notification (vftable slot 3, 0x109069A0).
- `src/code/engine/splinepath.cpp` (0x10910550 - 0x10911500): `engine::SplinePathCV` (a virtual-destructor point of 0x24 bytes:
  `key` = time at +4 and position at +8, tension, continuity, bias, forceSpeedMatch), `engine::SplinePath` (an
  `engine::IPath`, the points as `ArrayDynamic<SplinePathCV*, AllocatorNew>` at +8, the matrix at +0x18, the
  `math::Spline` built from the points at +0x58) and the path interface's class info. 51 functions match. EQUIVALENT:
  `CreatePoints` 0x10910EB0 (xmm register allocation, 66.8 %) and the destructor 0x10911410 (the independent spline
  pointer load sits before the array reset, 89.7 %). The point array's helper `Insert` / `Erase` are explicit member
  specialisations in splinepath.cpp (the pointer array's loops differ from the struct array's), and `Reserve` in
  arraydynamicallocatornew.h now declares its loop variable inside the else branch (shared header; the fmv matches stay 100 %).
- `src/code/engine/surfacedefinition.cpp` (0x10911500 - 0x10911880): `SurfaceDefinition` (global namespace; a game object
  handle at +8, a name at +0x10 and the three `StringC<260>` members physicsObjectReference +0x18, soundEffectName +0x120,
  decalName +0x228). The string members' offsets come from `StringBufferOffset(&base->member) + offsetof`, where the
  engine passes the address of the member in an object at 0x11276934 (`gStringMemberBase`; the result does not depend
  on it, but the call's argument is part of the code). The constructor is EQUIVALENT (the lea of the handle member is
  behind the reference count store in the engine, as in the camera loader, 92.2 %).
- `src/code/engine/actorspawner.cpp` (0x10905BC0 - 0x109067F0): `engine::ActorSpawner` (objectName +0x50, playerIndex
  +0x58, the spawned object's handle +0x5C; a word at +0x4C nobody writes) and `engine::ActorCrowdSpawner` (baseName
  `StringC<32>` at +0x4C, baseTransform +0x70, numAlongX / numAlongZ +0xB0 / +0xB4, grid spacings +0xB8 / +0xBC, the
  handles of the spawned objects +0xC0). `GameObjectSpawner` is 0x4C bytes, so the actor's 8-byte-aligned name starts
  at +0x50. EQUIVALENT: `SpawnGrid` 0x10906450 (stack slots of the loop counters, 96.6 %). NONMATCHING:
  `ActorCrowdSpawner::IsReady` 0x109063C0 (the engine repeats the whole handle lookup for the object, 35 %).
- `src/code/engine/driving/` (0x10905A00 - 0x10905BC0, 0x10906C40 - 0x10907020): `VehiclePhysicsAttributes` (the 0x1C-byte
  `VehicleMassAttributes` at +8), `CarPhysicsAttributes` (suspension +8, control +0x48, two groups the reflection does
  not show at +0x84 / +0xEC, 0x210 bytes) and `HelicopterPhysicsAttributes` (control at +8); the groups are structs of
  another unit (0x10934120 - 0x10937200) of which only the size, constructor and reflection are declared, mapped to
  the engine's addresses. `gVehicleVector` (0x1131B4B4, set by 0x10905A50) is the vector the driving system shares. The
  three constructors are EQUIVALENT: the engine's lea of the first member sits behind the volatile reference count
  store of `LoadObject` where ours hoists it above it (the same difference as in the camera loader and
  `SurfaceDefinition`; it recurs in every reflected class that derives straight from `MetaLoadObject`). Not done:
  `WheelCollectionData` (0x10907020 - 0x10907C40: its element array of `WheelData` needs destructors in the array
  header), the character solver (0x10907E90 - 0x1090C110, one unit with `CharacterSolverBehaviour`).
- `src/code/engine/world/locationrendersettings.cpp` (0x10914850 - 0x10914AB0): `engine::world::LocationRenderSettings` (the first
  one made is the current one, `sCurrent` 0x1131C67C): 10 functions match, the constructor is EQUIVALENT (store order,
  73.7 %). The inline accessors are defined in the source file so that their kept copies count.
- `src/code/engine/motionfeatureextractor.cpp` (0x10914AB0 - 0x10915450): the motion feature extractors (a pure base,
  the projected extractors with their `rootSpaceProjectionAxis` and the six leaf classes whose `Extract` reads the
  displacement, speed or acceleration along or around the axis). `LinearDisplacementExtractor::Extract` is EQUIVALENT (the
  last product's operand order, 95.9 %). The two class meta types of the base (0x10911DD0) and of the projected
  extractor (0x109151C0) are template instances of other units' neighbourhood. The leaf classes' deleting destructors
  are in the factories' unit (0x108D8BF0, 0x108DE390 ...).
- `src/code/engine/namedinventorycreator.cpp` / `remotecamera.cpp` (0x1090D720 - 0x1090DA00, 0x1090DA00 - 0x1090DDD0):
  `engine::NamedInventoryCreator` (the inventory's name at +8, its initial size at +0x10 (rounded up to a power of two
  when it is loaded) and the inventory it created at +0x14, held through `core::RefAssign` / `core::SafeRelease`) and
  `engine::RemoteCamera` (position, target and up vectors at +8 / +0x14 / +0x20, FOV, near and far plane, an active
  flag; 0x3C bytes). Both constructors are EQUIVALENT (store order of the reference count and the first member, 81.2 %
  and 71.6 %). Not done in this stretch: `GameObjectTemplateBuilder` (0x1090C110 - 0x1090D700, its metaobject template
  arrays and the 678-byte load function).
- `src/code/engine/secondaryphysicsjoints.cpp` (0x10915FD0 - 0x109179F0): the secondary physics joint drivers. The
  interface `SecondaryPhysicsJointDriver` (six vftable slots; its class info, member list and default slots are
  0x10937750 - 0x10937810, another unit) owns `GetHandleCount` constraint handles of the properties' handle array;
  `SecondaryPhysicsAmbientWind` (windForceScale +4, constantDirection +0x10), `SecondaryPhysicsPinJoint`
  (constraintPointOffset +4) and `SecondaryPhysicsPoweredJoint` (the force curve array of `ForceCurvePoint` (angle in
  radians, maxOrientationForce) at +4, dampingConstant +0x14, maxAngularVelocity +0x18 (radians, reflected in
  degrees through accessors)). Slot 2 of the pin and powered joints creates the constraints through ravenphysics
  creators (0x1065B6E0 / 0x1065B8A0 / 0x1065B760, names guessed; they return a handle through a hidden pointer, which
  is why the local `handle` pointer is needed to reach the engine's stack use). EQUIVALENT: `EvaluateForceCurve`
  (the engine keeps the previous point in esi, 21.9 %). NONMATCHING: the wind's slot 5 (x87 stack use of the last random number, 58.0 %). Not done: the pin joint's
  slot 4 (0x109164A0) and the powered joint's slots 3 and 4 (0x10916B10, 0x10916F20), which drive constraint
  setters of the physics library that are not reconstructed. The three drivers' shared fixes: the sizes of
  `ActorCrowdSpawner` (0xD0) and `CarPhysicsAttributes` (0x218) now carry the tail words the engine's factories
  allocate.
- `src/code/engine/trackedmotiontoexpressionmap.cpp` (0x10911880 - 0x10914850): `engine::TrackedMotionToExpressionMap` (a
  skeleton at +8 and an expression group at +0xC, both released through `core::SafeRelease`, and the array of
  `JointData` at +0x10; 0x20 bytes) with its three reflected structs: `PropertyMappingKeyValuePair` (key, value),
  `PropertyMapping` (0x30 bytes: the feature extractor it owns at +0, the expression's name at +8 and index at +0x10,
  weight, `BlendType` enum (Add / Min / Max / Override) at +0x18, the curve array at +0x1C, debugDisable at +0x2C)
  and `JointData` (0x78 bytes: the joint's name, an offset transform whose translation the reflection reads through
  an accessor pair, the motion filter it owns at +0x60, the mappings at +0x64, debugDisable at +0x74). 141 functions
  match, among them all the reflection, constructors, destructors and the template instances of the three element
  arrays. Not done: the per-frame update (0x10911FA0 / 0x10912AE0), the arrays' `Reserve` / `ShiftUp` /
  `ConstructFill` / `AssignRange` instances of `PropertyMapping` and `JointData` and the helper `Insert` / `Erase`
  slots (the engine expands the elements' copy construction and assignment inside the array functions, ours calls
  them), and two NONMATCHING functions: `PropertyMapping::IsCurveSorted` 0x10911E30 (15.8 %) and `EvaluateCurve`
  0x10911E60 (the interpolation is computed on the x87 stack by ours, 2.1 %). Shared headers: `ArrayDynamic<T,
  AllocatorNew>` (code/container/arraydynamicallocatornew.h) now has the engine template's destructor, copy
  constructor, assignment and element destruction in Clear / Free / Erase / ShiftUp / Reserve, an `allocator`
  member (the arrays are 16 bytes, which made the manual padding words of the fmv subtitle manager, the spline path,
  the powered joint and the actor crowd spawner unnecessary; their destructors lost their hand-written array
  frees, which made the powered joint's destructor match) and `ArrayEraseInline<T>` (the inline element loop or
  the call of `AssignRange`). `pure3d::Skeleton::FindJoint` (0x106DDA60) is declared in pose.h, and
  `pure3d::ExpressionGroup` is in pure3d/expressiongroup.h.
- `src/code/engine/secondaryphysicsproperties.cpp` (0x1090DDD0 - 0x10910550): `engine::SecondaryPhysicsProperties` (the
  physics data object a constructor makes at +8, the array of `JointData` at +0xC; 0x1C bytes). `JointData` (0xA0
  bytes) is a joint's collision volume: name, array of drivers (deleted with the joint), a reference to the mass
  properties, gravity flag, volume type (Sphere / Capsule / Cylinder / OBB), radius, centre offset, half length, the
  rotation type (XYZ / YZX / ZXY), the orientation matrix at +0x3C that the reflected angles in degrees (+0x7C) rebuild
  through their setters, and the debug display data. 112 functions match (the reflection, constructors, destructors,
  the small accessors and the template instances of the driver and joint arrays); the constructor is EQUIVALENT (the
  engine pushes edi after the first stores, 95.7 %). Not done: the physics-object construction (0x1090E540, 0x1090E600,
  0x1090E820, 0x1090F200, 0x1090F420, 0x1090F470, which call into the physics library) and the joints' copy
  constructor, assignment and `Reserve` (0x1090F8C0, 0x1090FCE0, 0x109101D0; the engine's copy of the orientation
  matrix goes through a vector-copy helper). Shared: `content/enummetatype.h` (EnumMetaTypeGetSet and the global
  EnumMemberGetSetter), `ravenphysics/massproperties.h` (the size-only class moved out of reflectedclasses.h), the
  YZX / ZXY Euler rotations declared in matrix.h (0x107CEF70 / 0x107CF0A0, names guessed), and in
  arraydynamicallocatornew.h the helper for pointer arrays (`ArrayDynamicHelper<ArrayDynamic<P*, AllocatorNew> >`,
  which replaces the spline path's own) and the `CopyRange` mode of `ArrayEraseInline`.
- `src/code/engine/driving/wheelcollectiondata.cpp` (0x10907020 - 0x10907DC0): `engine::driving::WheelCollectionData` (the
  physics object factory it takes the body from at +8, the skeleton at +0xC and the array of `WheelData` at +0x10;
  0x20 bytes). A `WheelData` (0x68 bytes) is a `StringC<64>` name member at +0 followed by two words and seven floats
  (its reflection and default constructor are in the 0x109375xx unit). 39 functions match, including the array
  instances of the wheels (the string member is why the array destroys an element with a store of the string base's
  vftable). Not done: the four-wheel default setup (0x10907C40, a declared member the load notification calls), the
  arrays' `AssignRange` / `Resize` (the engine allocates its registers differently) and the helper's default element
  accessor. `StringC<N>` got the engine's assignment (the bounded copy), and `ArrayDynamic<T, AllocatorNew>` the
  `Resize` and range `Erase`; `ravenphysics/physicsobjectfactory.h` holds the size-only class.
- `src/code/engine/charactersolverproperties.cpp` (0x10908490 - 0x109086A0): `engine::CharacterSolverProperties`, a content
  library object (`MetaLoadObject`) with seven reflected floats and flags that tune the character solver (maximum linear
  acceleration, maximum steering angular force, maximum push velocity, whether platforming is on, the effective character
  mass on a platform, the minimum mass ratio for platforming and the maximum velocity gained from a platform). 10
  functions match; the constructor is EQUIVALENT (the engine loads each default right before its store, ours loads them
  up front, 42.7 %).
- `src/code/engine/fight/behaviours/motiontreebehaviour.cpp` (0x1091F380 - 0x1091F890): `engine::MotionTreeBehaviour`, the
  fight tree behaviour that runs a motion tree: it keeps the pending message flags and the auto-resequence setting
  (reflected as `autoResequence`), listens for the sequencer to be ready and resets the sequencer on one message. 15
  functions match. `UpdateListening` is NONMATCHING (41.2 %, the engine keeps the sequencer test's result in a stack slot
  across the branch); `Sequencer::Unknown105A4270` is declared for the update.
- `src/code/engine/firstpersoncontrolbehaviour.cpp` (0x1091DF60 - 0x1091EC70): `engine::FirstPersonControlBehaviour`
  (0x34 bytes): the behaviour that lets the player look around from the eyes of its owner, with the reflected `invert`,
  `horizSensitivity`, `vertSensitivity`, `vertDeadZone` and `speed`. 12 functions match: the reflection, the
  constructor (it makes the owner's "EYEPOINT" matrix attribute, `GameObject::SetAttributeAndGet<math::Matrix>`, an
  out-of-line template instance in another unit, and the name global `gEyePointName`), the slot 1 that starts the
  camera transition for the controlling player. Not done: the update (slot 4, 0x1091E360, 2158 bytes, mapped to the
  engine's) and the character override message it sends (0x1091E1B0).
- `src/code/engine/knockbehaviour.cpp` (0x1091EC70 - 0x1091F380): `engine::KnockBehaviour` (0x24 bytes): pushes the
  objects in front of its owner away (reflected `strength`, `rangeDistance`, `rangeCosHalfAngle`,
  `minimumRepeatPeriod` and `damage`). 12 functions match (the reflection, the constructor, the empty slot 1); the
  update (slot 4, 0x1091EDA0, walks the world's object list) is mapped to the engine's.

## 0x10880000 - 0x108A0000 (sn-t): the online layer's users, the front end input, the exception manager

About 740 of the range's 1557 functions are reconstructed (including the kept copies); the rest is listed under
"Not started". Units, in address order (all file names are guesses, there is no assert path in the range):

- `engine/controller/physicalcontrollermapmanager.cpp` (0x10880AA0 - 0x108810F0, 0x10882140 - 0x108822C0): the
  controller maps (`ControllerMap`, `ButtonMapping`, `AxisMapping`, the eleven-row `gControllerKinds` table at
  0x111D17B0) and `PhysicalControllerMapManager`. `OnConnected` is EQUIVALENT (95.8 %, the slot is extended before the
  controller is loaded in the engine). `core::IControllerListener` is now `core::IControllerConnectionChangeCallback`, the name
  the RTTI gives it.
- `engine/frontend/feinputhandler.cpp` (0x108810F0 - 0x10882140): `FEInputHandler`, `UpdateFEInput`, the dead zone and
  cursor handling. `engine::controller::Keyboard` (was `Updater`) with its callback list, `SlotManager::GetKeyboard` is a
  static. EQUIVALENT: `OnKey` 21.7 % (frame slot of the two characters), the destructor 54.5 %, `UpdateFEInput` 99.1 %.
- `engine/gamestate.h`, `engine/pausestate.cpp` (0x108822F0 - 0x10882700): `PauseState`. NONMATCHING: `Enter`
  0x10882320 (47 %), `Leave` 0x10882380 (88 %); the engine compares the context member in memory and loads it again for
  the call.
- `engine/system/exceptionmanager.cpp` (0x108826C0 - 0x10883550): `ExceptionManager` (three bases: OLS callback, input
  callback, console manager callback; each virtual is compiled with the sub-object `this` of its base, the offsets in the
  bodies are relative to it), its four `ExceptionFEPopUpDialogState`s (lobby, peer, controller, media), the handler
  list (`AddHandler` / `RemoveHandler` / `Notify`, four slots at 0x11316D6C), the pause watch flags (0x11316D80 /
  0x11316D81 and the callback at 0x11316D84), `CreateExceptionManager` and the drive error thread (`StartDriveErrorThread`,
  `DriveErrorThread`, `StopDriveErrorThread`, the fault flag 0x11316DA0). EQUIVALENT: `Slot3` 37.8 % and `OnMessage`
  33.8 % (the engine makes the dialog call's minus one in a register and jumps from the failed first message test to
  the second), `Slot6` of the dialog 45.3 % (loop alignment, ecx load), the constructor 97.5 % (the `or eax, -1` sits
  after the base vftable stores), `Update` 66.8 % (the engine keeps -1 in edi for compares, stores and the interlocked
  masks), `DriveErrorThread` 90.4 % (eax / edx swapped for every virtual call). `ConsoleManager::Callback` got an
  inline constructor overload (`Callback(bool)`) because the engine inlines the constructor here. `DialogState`'s
  `Unknown10883D50` takes (controller, flag), `Unknown10883D70` answers a bool. `OLS` got named members +0x7C (`session`,
  one virtual slot used), +0x80 (`userTable`, entries of 0x40 bytes), +0x88 / +0x8C (`localUsers`).
- `engine/frontend/valueformat.cpp` (0x108833E0 - 0x10883A90): the text forms the front end's messages ask for
  (`FormatInteger`, `FormatFloat2` / `5`, `FormatMoney`, `FormatMoneyCents`, `FormatTimeOfDay`, `GetMouseButtonName`,
  `GetValueText`, `FormatMessage` with the `%n:NAME` places and the table `gValueFormats` at 0x111D2D50, `TranslateValue`,
  `FormatString`, `FormatBracketed`). EQUIVALENT: `FormatTimeOfDay` 72.7 % (the engine puts the chain for the hours after
  noon behind the return), `GetValueText` 83.7 % (value and type swap registers). Not done: `BUTTON` form 0x10883A90
  (526 bytes, controller button names), 0x10883720 / 0x10883820.
- `engine/frontend/dialogstate.cpp` (0x10883CB0 - 0x10883FE0) and `femovie.h`: `DialogState`, `FEPopUpDialogState`.
  EQUIVALENT: `GetController` 88.9 %, `OnCall` 82.3 %.
- `engine/online/`: `ConsoleManager::Callback` (0x10882BC0 and its five empty slots), the user / game / profile storage message
  constructors, `OLSProfile` (declared), the script method wrappers.
- `engine/nis/`: the NIS player, its scene structs, reflection, array meta type helpers
  (`GetArrayCMetaType`, `GetMemberColourMetaType`) and the Lua natives (`PlayNIS` EQUIVALENT 67 %, the dead vftable store).
- `engine/system/skuinfo.cpp`, `engine/system/simulationdriver.cpp` (the driver class made of what `gamestate.cpp` kept
  as stubs), `engine/effectparams.cpp` (`EffectParams` constructor EQUIVALENT 63 %), `engine/lightbehaviour.cpp` (the
  reflection of the light behaviour, 52 members, and the light messages), `engine/system/streamdriverbehaviour.cpp`
  (reflection, construction, trigger and package lists, the package sort; `Unknown10899770` EQUIVALENT 95.2 %),
  `engine/system/streamclient.cpp`.
- `engine/controller/defaultcontrollerhandler.cpp` (0x10895BD0 - 0x10896440): `DefaultControllerHandler`. EQUIVALENT: the
  constructor 90.5 % (the dead base vftable store), `UnlockAllControllers` 80.3 %, `Slot3` 77.6 %, `Slot4` 75 %,
  `SetController` 55.1 %, `Slot7` 72.2 %, `Slot8` 59.4 % (all: the engine makes the minus one with `or` and
  pushes the locked controller before the physical manager).
- `engine/database/gamedbhelper.cpp` (0x10894450 - 0x10894830): `GameDBHelper` (an OLS callback that makes the account
  and settings subjects of the database when it starts and releases them when it stops). All 11 match.

Lessons: (1) `long value = ReadValue(p); return value != 0;` is the shape of the engine's inline interlocked read when the
result is a bool; the one-line `return (read) != 0;` compiles to a `neg / sbb` pair. (2) `while (!cond) body` with the
condition made of calls is inverted by the compiler into test, body, test; a `for (;;)` with a `break` keeps the
engine's jump back to the top. (3) The engine's text formatter reads like a loop with a `continue` for the percent
sign; writing the branches as `if (c != '%') { ... } else { ... }` with the `index <= 9` test first gives the same
block order. (4) Copying a union's 8 payload bytes as `unsigned __int64` gives the two `mov`s the engine has, the
`double` copy goes through the FPU. (5) `or reg, -1` as the source of a stored or pushed minus one appears in the engine
wherever the compiler's constant hoisting saw several uses; ours folds single uses back into immediates (open question,
see the EQUIVALENTs above).

Not started: the filesystem enumeration and cement library glue (0x10883FE0 - 0x10884E61, 72 functions of containers and
lookups that belong to the 0x108E6000 range), the Flash handle table (0x108854E0 - 0x10885CDA), `OLSUser` (0x10886A70 -
0x108879EA, a 0x38-byte entry container plus the platform proto class), `OLSGame` (0x10887D60 - 0x1088831E), `OLSProfile`'s
own functions and `OLSProfileStorage` (0x10889C50 - 0x1088B6D4), `MonkeyControllerManager`, `DebugCamera`,
`PlaybackTreeBehaviour`, `OnlineGameDBHelper` (0x108939A0 - 0x10894450, a class of three bases and a reply queue), the
advertisement client (0x10894840 - 0x10895540, third-party code), the audio player's physics tail (0x10880010 -
0x10880650), `StreamDriverBehaviour::OnMessage` (0x10899370), `LightBehaviour`'s constructor, update and controller,
and the list template instances at 0x10880800 - 0x10880A70.
- `src/code/engine/fight/branch.cpp` (0x105A2B10): `fight::Branch::MoveChild` is NONMATCHING (the registers of the child, the
  parent and the list walk are allocated in another order).
## 0x10840000 - 0x10860000 (sn-s): the lua vectors, the triggers, the props, the cameras and the render scripts

- `src/code/engine/luavector.cpp` (0x108400A0 - 0x10841040; the Lua binding of `math::Vector` and `core::Name`): 27 functions
  match and 21 are EQUIVALENT (the metamethods and the argument checks compile with other registers). The lua.h calls
  the binding needs are declared there.
- `src/code/engine/propbehaviour.cpp` (0x10841060 - 0x10841550): `engine::PropBehaviour` (a plain `Behaviour`, 0xC bytes).
  Its constructor makes the object's PropSpawner attribute (`GameObject::SetAttributeAndGet<PropSpawner*>`, the engine's
  instance sits in this unit: it looks the attribute up, makes it in the static list while the object is being
  constructed and in the dynamic one otherwise) and an empty "meta object template" name, and listens for the
  physics filter message (type 6: switches intersection property 0x40 on) and the "has the prop moved from its
  spawner" query (type 0x18, id 8: the spawner's position against the object's, `IsNear` with `EPSILON_SMALL`
  expanded in place). `ConstAttribute<T>` / `Attribute<PropSpawner*>` (the value sits at +4, one vftable slot) and the
  inline `BaseAttribute` destructor (gameobject.h) come from here. 19 functions match; not done: 0x10841120 and
  0x108411B0 (tail calls of `GameObject::FindAttribute` whose classes are unknown).
- `src/code/engine/metabehaviourcreator.cpp` (0x10841F80 - 0x10842010): the base of every behaviour creator (2 functions
  match): the creation makes the behaviour for the object being constructed in its heap and registers it unless it is
  a behaviour controller.
- `src/code/engine/trigger/volume.cpp` (0x10841550 - 0x10841F80): `engine::trigger::Volume` (kind, interaction mask, the
  physics object's handle and the owner), `SphereVolume` (0x24 bytes) and `OBBVolume` (0x50): the volume follows the
  transform of its owner as an object of the physics library. 41 functions match (the whole unit, with the
  reflection and the three scalar deleting destructors, which are the compiler's: a derived destructor without a
  body of its own calls the base's directly, so none is declared). `ravenphysics::CreateObject` (0x1066AA80)
  takes an `ObjectProperties` (the intersection properties and a zero word, which is the extra local of the
  engine's frame).
- `src/code/engine/propspawner.cpp` (0x10842010 - 0x10842F00): `engine::PropSpawner` (a `GameObjectSpawner` with the
  handle of its object at +0x4C, a name, the scale vector and the shared `UnpackedInitialState` at +0x64) and
  `UnpackedInitialState` (the `TreeState` array that a string "prefix:state,state" unpacks to; LoadObject with an
  `ArrayDynamic<TreeState, AllocatorNew>` base, 0x20 bytes). 42 functions match, among them the class's reflection
  (the scale vector and the "initialState" string whose setter is also given the inventory:
  `StringMetaTypeGetSetWithResolver` and `StringMemberGetSetterWithResolver<C>` in content/stringmetatype.h), the creation
  of the object and the many template instances; `UnpackedInitialState::UnpackedInitialState` is EQUIVALENT (the engine
  writes an unused byte of its frame earlier, 92.7 %). Not done: `Apply` (0x108427E0, NONMATCHING 69.4 %, the engine
  expands the scale writer's lookup in each branch and stores through the pointer it holds in a register), the
  inventory lookups 0x10842660 / 0x108426C0 / 0x108429B0 (slot 6 of the inventory), the `AttributeWriter<Vector>`
  destructor and the `DynamicCaster<PropSpawner>` instance. `engine::AttributeWriter<T>` is 0x18 bytes (a word after
  the value pointer) and takes the value pointer first: that made three Lua attribute natives (`go_SetIntAttr`,
  `go_SetFloatAttr`, `go_SetVectorAttr`) match that were EQUIVALENT with a frame four bytes larger.
- `src/code/engine/database/dbsubject.cpp` (0x10842F10 - 0x10843F50): `DBSubject`, `DBChange` and `DBSubjectInfo`, the
  database value with its observers and pending changes. 60 functions match, 3 EQUIVALENT; the second instances of
  the list iterators and allocators (0x10843150 - 0x10843300, 0x10843780 - 0x10843870) are not done.
- `src/code/engine/controller/physicalcontroller.cpp` (0x10845B50 - 0x108474E0): the physical controller and its rumble
  effects: 24 functions match, 7 EQUIVALENT, `Bind` NONMATCHING. `ReadMouse` (0x10847150) is not done: it copies the
  display's settings (0x10623670) and reads the sensitivity table at 0x111C73A4.
- `src/code/engine/healthbehaviour.cpp` and `src/code/engine/hitreactionbehaviour.cpp` (0x10847xxx - 0x10848xxx): 31 and 11
  functions match, 2 and 1 EQUIVALENT.
- `src/code/engine/commandline.cpp` (the command line options, 7 functions match, 2 EQUIVALENT) and
  `src/code/engine/render/renderscripts.cpp` (0x10849xxx; the renderer's script functions and their registration:
  22 functions match). `engine::DrawableRegistry` (drawableregistry.h) is only declared as far as the scripts call it;
  the rest of its unit (0x10849070 - 0x1084CBB0: the `RenderTask`, the effect controller, the decal creators, 3749
  bytes for the deformable decals) is not done.
- `src/code/engine/camera/` (0x1084CBB0 - 0x10853000): the camera system.
  - `camera.cpp`: `engine::camera::Camera` (0x48 bytes: the base of every camera, with the name, the player, the pure3d
    camera, the registration with the Director and the slot / id pair `ControllerRef`) and `ControllerRef`: 33 functions
    match.
  - `cinematographer.cpp`: `Cinematographer` (0x7B0 bytes: the director of one view; blends between the controlling
    camera, the animated and the blend camera; its default camera is the `DebugCamera`), the state it keeps
    (`CameraHistory`, 0x6F0 bytes) and the reflected `CinematographerType`: 35 functions match.
  - `camerabehaviour.cpp` / `cinematographerbehaviour.cpp`: the behaviours that put a camera / a cinematographer into
    an object: 18 + 18 functions match, with the mirrored copy of the pure3d camera's matrix into the owner's
    transform (the engine copies the rows through `Vector4` temporaries that are all loaded before they are stored).
  - `scriptedcamera.cpp`: the camera that plays splines or a pure3d animation (position, look-at and up tracks,
    bound to a part of an object): 28 functions match, 8 EQUIVALENT; `Update` (0x10851CA0) is NONMATCHING (11.2 %: the
    engine builds the mirrored view of its last case from rows copied by out-of-line `Vector4` and `Matrix` copy
    constructors).
  - `blendcamera.cpp`: the camera that blends between two snapshots: 12 functions match, 2 EQUIVALENT; `Update`
    (0x108528A0, 2375 bytes) is not done.
  - `dramaticcamera.cpp`: the camera that plays up to four queued animations and checks them against the world with
    rays: 13 functions match, 2 EQUIVALENT (`Play`, and `SamplePath` 0x1084F240 which samples the position channel of
    an animation at up to 32 points; the engine holds the animation in ebx and the buffer in edi, 68.7 %);
    `FindAnimation` (0x1084F420) and `Update` (0x1084F9D0) are not done (a random pick over weights with an inlined
    `math::Random`, and a long SSE function).
  - `cameramath.cpp`: the easing and the vector helpers of the camera: 13 functions match, 5 EQUIVALENT, 1 NONMATCHING.
  - `director.cpp`: the camera director's functions that belong to this range (70 functions, 3 EQUIVALENT).
- `src/code/engine/reflectedmath.cpp`: the reflection of the math types (AABB, OBB, Plane, Sphere, Vector) and the
  message base classes: 28 functions match.
- `src/code/engine/playerintentions.cpp` (0x1085B810 - 0x1085BD10): the table of the eight players' intention maps and the
  two locomotion axes: 5 functions match (the reference-counted assignment instance included).
- Shared headers changed by this range: `GameObject` got the `SetAttributeAndGet` overload without the flag,
  `AttributeWriter` its real size and constructor, `BaseAttribute` an inline destructor; `Camera` got the word at
  +0x44 (the derived classes start at 0x48) and `focusDistance`; `pure3d::Animation::GetGroup`,
  `math::Vector::IsNearOther` (the engine's second copy of `IsNear`), `container::ArrayDynamic<T, AllocatorNew>::PushBack`,
  `SetPropLogicStateMessage`'s inline constructor and the resolver variants of the string meta types are new.

## 0x105E0000 - 0x10600000: the music cells and cue events, the audio renderer driver, the om stream and method classes, the content meta types (sn-u)

Done (functions match unless noted):
- `music/cell.cpp`, `music/cueevent.cpp`, `music/cellplayer.cpp`: `Cell` / `MGraphCell` (their binary reader and writers
  included), the 17 cue events and their reflection (properties, methods, enumerations), the template instances of the
  reflection library they use, and the typed `Invoke` slots of all their methods (`om/invoke.h`: `ReadArgument<V>`,
  `GarbageList`, `StreamContext`). EQUIVALENT: `MetaProperty<unsigned __int64>::SetBinary` / `GetBinary` (0x105F12F0 /
  0x105F1340, register allocation), `MetaProperty<const FollowAction&>::SetText` (0x105E21F0), `MGraphCell::ReadBinary`
  (0x105E24A0, 97.6 %, the order of two loads at the end).
- `audio/rendererdriver.cpp`: `RendererDriver` with its reflection. NONMATCHING: the constructor 0x105E65E0 (32.7 %, the
  engine builds a temporary string and copies it).
- `om/memorystream.cpp`, `om/bufferedstream.cpp`, `om/metamethod.cpp`: EQUIVALENT `BufferedStream` constructor / `Read`,
  `MetaPropertyBase` constructor; NONMATCHING `TreeHead::InsertByName` for the property and method trees (0x105E4210 /
  0x105E4430, about 15 %: the engine keeps the halves of the 64-bit key in registers across the loop).
- `content/metatype.cpp` (the meta type base, its flag characters, `IsDirect` and the meta heaps), `content/metastream.cpp`
  (`BinaryReader`, `BinaryWriter`, `TextReadStream`, `TextWriter`, the type names), `content/vectormetatype.cpp`,
  `content/classmetatype.cpp` (the class meta type: members, base class, derived list, all twelve slots). EQUIVALENT:
  `TextReadStream::ReadToken` (0x105FC1F0), `ClassMetaType::FindDerived` (0x105FA960, the engine does not turn the
  recursion into a loop), `CompareMembers` (0x105FB010, base / index order of two addresses), `ReadText` (0x105FB230, stack
  slots of three locals).

What the matching taught:
- A call of a meta type's slot through `MetaType::Invoke...` or a cast function does not give the engine's code, a cast of
  the pointer itself to `MetaTypeView` (content/metatype.h) does: the compiler then reads the slot's address before it
  works out the arguments and reads the object again afterwards.
- `MetaType::Matches` is slot 5 and `MetaTypeBase::WriteBinary` answers a bool (the enumerations' `WriteBinary` returns the
  result of `WriteInt`, which was why those instances looked like register allocation differences).
- The small identical functions of the reflection (allocation tags, operator new / delete of the holders, `Garbage<V>`)
  can only be told apart by who calls them: the callers in `ReadArgument<V>` fixed the addresses of the tags of `Fade`,
  `FollowAction`, `MGraphCellPlayer`, `Garbage<Fade>`, `Garbage<FollowAction>`, `Garbage<float>`, `Garbage<State>`,
  `Garbage<Bool32>`, `Garbage<unsigned int>` (symbols.txt and the annotations of `music/time.cpp` follow them).

Open in this range (about 1000 functions, 250 of them only mapped):
- `MGraphCellPlayer` / `CellPlayer` (0x105E29C0 - 0x105E3F00, about 35 functions with the 884 and 1297 byte ones), the
  registration functions of the reflected classes (0x105F4130 - 0x105F6EE0: one pair per class, 72 + 467 / 843 bytes; they
  build `om::Name`s from strings, the classes' `MetaClass`, methods and properties; the getter pointers they take are the
  engine's folded copies), the ADPCM block decoder (0x105EB030 - 0x105EB5C0, written with branch-free selects), the
  `Rpc*` classes (0x105F8800 - 0x105F9A90), `content::ArrayDynamicMetaType` and its helper (0x105FD3C0 - 0x105FE340, the
  text reader 0x105FE340 is 785 bytes), `EnumMetaType`, `NameMetaType` (four name types selected by two flags),
  `ReferenceMetaType*`, the chunk handlers and the P3D loaders (0x105FF000 - 0x10600000).
