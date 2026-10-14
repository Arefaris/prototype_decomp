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

## render/async/private/renderglobals.cpp (0x10817A10 - about 0x10818F00): 13 functions, 10 match, 3 EQUIVALENT

The drawable table (0x1130CCC4: slots, serials, count), the render event allocator (0x1130CCDC, slots 3 / 4), the
deferred deletion list and the render event queues. Each queue is a template instance (two queues, 0x11284C60 and
0x11304C90, with identical copies of every helper): a ring of 0x20000 values behind a free and a ready semaphore,
lock-free read / write indices and a commit structure at +0x10 (0x10817F90, not reconstructed) that releases the
slots that became readable. Only the first queue's instances are mapped. Notes:
- The two "FATAL: Async render event queue overflowed..." asserts are OLD_ASSERT_AT with the original line numbers
  (0xA9, 0xBE).
- ExecuteRenderEvents is `while (TryPop(&queue, &event) && event != 0) event->Execute();`.

| Address | Name | Status | Notes |
|---|---|---|---|
| 0x10817A50 / 0x10817AD0 / 0x10817B10 / 0x10817B40 | AllocRenderEvent / FreeRenderEvent / GetRenderList / DeferDelete | match | |
| 0x10817F40 | AllocAsyncQueueSlot<RenderEvent*> | EQUIVALENT | same loop, other registers for the index pointer and the slot |
| 0x10818260 / 0x10818920 | IsValidDrawable / GetDrawableData | EQUIVALENT | the original loads the whole handle and masks the index; every form tried (masks, bitfields, accessors, volatile) loads it as a word |
| 0x108185F0 / 0x10818620 / 0x10818C00 / 0x10818C60 | Reserve / Commit / TryPush / TryPop<RenderEvent*> | match | template functions with the queue as first argument |
| 0x10818CC0 / 0x10818DA0 | PushRenderEvent / ExecuteRenderEvents | match | |


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
| 0x106E41C0 / 0x106E6350 / 0x106E69B0 | ChannelKeys<float / CompressedQuaternion6 / CompressedQuaternion8>::Evaluate | match |
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
