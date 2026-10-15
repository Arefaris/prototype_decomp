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


## engine/physics/physicsmanager.cpp (0x107E2440 - 0x107E7A00), started

The unit's assert path (`..\..\..\code\engine\physics\physicsmanager.cpp`, lines 0x794 - 0xA4F) names it; its
functions run from 0x107E2440 (right after `engine::MasterTable`'s constructor) to 0x107E75F0 (2598 bytes) and the
unit registers the `pm_*` console commands (0x107E6F20). One source file holds everything in the range: the
collision messages, the shared query buffers and the manager's Lua commands share one translation unit (the small
class at 0x107E2BF0 that reads the pad axes is constructed by 0x107E3710, so the "climbing" input map is part of
it too). 44 functions match so far, in address order:

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

NONMATCHING:

- 0x107E37B0 AtomicExchange: the engine's copy takes the value in `eax` (a link-time code generation convention),
  ours in `edx`; 60 %.

Not done (owners or layouts not recovered yet):

- 0x107E3830 - 0x107E3860, 0x107E3AC0 - 0x107E3B00, 0x107E3B60 / 0x107E3B70, 0x107E3B80 / 0x107E3BC0: accessors of
  classes the unit's messages and manager own (member offsets 0x14, 0x1C, 0x70, 0xC0, 0xC2, 0xE0).
- 0x107E3D00 / 0x107E3D10, 0x107E3C00 / 0x107E3CB0 / 0x107E3CD0, 0x107E3D60: ravenphysics::Context wrappers and a
  constructor whose members are still unknown.
- 0x107E3DB0, 0x107E3DD0 (done) - 0x107E3F90 (the collision log), the container helpers 0x107E4340 - 0x107E4AE0,
  `ListObjects` 0x107E4F40, 0x107E4E10 / 0x107E4E60 / 0x107E4F00 (the object lookup by uid and by collision-object
  index), 0x107E4910 / 0x107E49B0 / 0x107E49E0 / 0x107E4A50 (the uid lookup loops), 0x107E52A0 - 0x107E6B70 (the
  remaining list commands, the `Function4` script wrapper 0x107E59C0 and the constraint dumps) and 0x107E6C40 -
  0x107E75F0 (the uid hash table, `Create` 0x107E7180, `Destroy` 0x107E6D30 and `Update` 0x107E75F0).
- 0x107E2BF0 and its 0x107E24B0 - 0x107E3290 neighbours (the pad-driven "climbing"/"wall_run" input map; the class
  is 0x58 bytes with a state pointer at +0x10 and a `Vector` at +0x34).

Shared headers touched: `code/ravenphysics/context.h` (the query buffer lock, `Context::SetSolverIterations`, the
`ObjectList` members at 0x14 / 0x1C and `Context::unknown0`).

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
| 0x108BC810 - 0x108BEF7F | not placed (73 functions) | `engine::render::LetterboxRenderPass`, `pure3d::DebugObjectManager` / `debugoverlay::DebugSelectionManager`, `engine::MotionTrail`, `MotionTrailCreator`, `MotionTrailState` (their six vftables are consecutive in `.rdata`) |
| 0x108BEF80 - 0x108C02C4 | not placed (55 functions) | `engine::OnlineManager` (0x108BEF80 / 0x108BEFA0 / 0x108BEFC0 register it and its peers), replay / CRC / desync reporting (0x108BF030 reads `ReplayMode`, `recordCRC`, `DesyncHunt`; 0x108BFD30 dumps a controller desync) |
| 0x108C02D0 - 0x108C04D9 | this unit (6 functions) | the pool |
| 0x108C04E0 - past 0x108C1000 | `code/engine/fmv/fmvsubtitlemanager.cpp` (not started) | `engine::FmvSubtitleManager` and its `SubTitleEnty` (0x10C bytes), the `content::ArrayDynamic` / `ArrayDynamicHelper` copies |

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

## engine/fight/behaviours/fighttreebehaviour.cpp and its neighbours (0x10862A60 - 0x10864EF0)

112 functions. The range holds **four** units; the boundaries are read off the class statics and the vtables, not off
the address order (the two units interleave their statics):

| unit | range | identified by |
|---|---|---|
| `code/engine/render/behaviours/renderbehaviour.cpp` | 0x10862A60 - 0x108638BF | ctor 0x108636B0 and deleting destructor 0x10862C10 install `engine::RenderBehaviour` (vftable 0x10E730C8, 8 slots); 0x10862F60 / 0x10862AC0 are its reflection statics; 0x10863060 is the message handler and its switch bodies and jump tables run to 0x1086369F; the five small functions 0x10863850 - 0x108638B0 sit between the ctor and the fight unit's `GetClassInfo` and are the only ones whose owner is not certain (they read +0x3C / +0x8 and call through a slot) |
| `code/engine/fight/behaviours/fighttreebehaviour.cpp` | 0x108638C0 - 0x108642B7 | `GetClassInfo` 0x108638C0, ctor 0x108639E0 and destructor 0x10863AC0 install `engine::FightTreeBehaviour` (vftable 0x10E7311C, 8 slots); the debug dump 0x10863C50 and the message handler 0x10863FB0 carry the assert path `..\\..\\..\\code\\engine\\fight\\behaviours\\fighttreebehaviour.cpp` |
| frontend (a Scaleform/HUD unit, no class static) | 0x108642C0 - 0x10864C2F | the `fe_*` Lua natives (`fe_SetUpdateEnable`, `fe_ToggleHideHUDOption`, `fe_SetMouseVisibility`), the mouse-cursor and HideHUD statics at 0x111CEF38-0x111CEF48 / 0x11315C58-0x11315C70, and the Scaleform screen calls 0x10872AD0 / 0x10873220 / 0x108816F0 |
| path behaviour (IPathBehaviour / PatrolPoint / SplineBehaviour) | 0x10864C30 - 0x10864EF0 | the five class statics 0x10864C30 / 0x10864C70 / 0x10864CB0 / 0x10864D00 / 0x10864D40 naming `engine::IPathBehaviour`, `engine::PatrolPoint`, `engine::PatrolPathBehaviour`, `engine::SplineCV`, `engine::SplineBehaviour` |

Done: **33 functions match**, nothing is marked NONMATCHING (the rest were not attempted, so no body was written and
nothing was excluded from the build).

- fight unit (7): 0x108638C0, 0x10863950, 0x10863970, 0x10863980, 0x10863990, 0x10863A90, 0x10863B90.
- path unit: the same trick below gives 0x10864FA0.
- `src/code/engine/frontend/frontend.cpp` (20, new): 0x108642D0 `fe_SetUpdateEnable`, 0x10864310 `SetFrontend`,
  0x10864330 `GetFrontend`, 0x10864340 `GetFrontendHeap`, 0x10864390 `SetScreenCentre`, 0x10864420 `GetScreenWidth`,
  0x10864430 `GetScreenHeight`, 0x10864440 `UpdateScreenCentre`, 0x10864490 `SetCursorFade`, 0x108644A0
  `GetCursorFade`, 0x108644E0 `SetCursorScale`, 0x108644F0 `GetCursorScale`, 0x10864500 `ResetCursorScale`,
  0x10864520 `GetScreenCentreX`, 0x10864530 `GetScreenCentreY`, 0x10864560 `ShouldHideHUD` (returns `int`, not
  `bool` - with `bool` the compiler emits `mov al, 1` where the original has `mov eax, 1`), 0x10864590
  `fe_ToggleHideHUDOption` (a `^= 1`, `!flag` compiles to `cmp`/`sete`), 0x10864AE0 `ResetLanguage`, 0x108649F0
  `SetLanguageName` and 0x10864A00 `GetLanguageName` (the `core::Name<core::CaseSensitiveKey>` at 0x11315C78). The
  unit has no assert path and no class static, so the file name, the free-function shape and every name are guesses.
- `src/code/engine/gameobject/behaviours/pathbehaviour.cpp` (5, new): the five reflection statics 0x10864C30,
  0x10864C70, 0x10864CB0, 0x10864D00, 0x10864D40. File name and header are guesses too.

Not done, by unit (each is a place to start, not a verdict):

- **fight unit**: 0x10863900 + 0x108639A0 (the context update: `GetHandle(owner)` into `context + 0xC`, the first one
  followed by the two 16-bit LCG steps of 0x111BDA0C); 0x108639D0 (`[ecx+8]` getter - the owner is at +4 and +8 is
  `Behaviour::state`, so this is probably a method of another class in the file); 0x108639E0 (ctor, `ret 8`: the second
  argument is the context, and `new (0x18) engine::GameObjectParams(0x10001)` - 0x107FC710 - when it is null);
  0x10863A80 + 0x10863A90 (kept copies of `BaseClassCasterImpl<engine::Behaviour, engine::FightTreeBehaviour>`
  ctor / `IsDerived`); 0x10863AC0 (dtor), 0x10863B00 + 0x10863FB0 (message handlers), 0x10863BA0 `SetBranch`,
  0x10863C00, 0x10863C50 (the "Fight Pre " dump, 751 bytes and recursive), 0x10863F40 / 0x10863F60 / 0x10863F70
  (`engine::FightBranchRefMemberGetSetter` ctor / Get / Set - vftable 0x10E73204), 0x10863F90 (`??_G`, a kept copy),
  0x10864180 + 0x108641E0 (`GetMembers`: the members are named **"fightBranch"** and **"sequencer"**, the base is
  `content::GetClassMetaType<engine::Behaviour>()` and the caster `BaseClassCasterImpl<Behaviour, FightTreeBehaviour>`;
  the getter/setter pair for the branch is `GetBranch`/`SetBranch` with the code string at 0x10D94FF4).
- **render unit** 0x10862A60 - 0x108638BF: nothing attempted. 0x10863060 is a `switch` whose case bodies and jump
  tables run to 0x1086369F although `functions.tsv` says 52 bytes (see the note below), and 0x10863850 - 0x108638B0
  are five 4 - 20 byte functions that read +0x3C / +0x8 and call through a slot.
- **frontend unit**: 0x108642C0 (`&member[0x5C]` of the frontend object - the object is 0x1238 bytes, built by
  0x10872D70, held in 0x11315C68), 0x10864350, 0x108643B0 (float clamp to +-120 then 0x108814F0), 0x108644B0 /
  0x108644C0 / 0x108644D0 (5-byte `jmp` thunks - linker artefacts, leave them), 0x10864540 `fe_EnableCatchupBehaviour`
  (`GetFrontend() + 0x2C` then 0x10885E10 - needs the frontend class layout), 0x108645A0 (shutdown), 0x10864600
  (1007 bytes), 0x10864A20 `SetLanguage`, 0x10864AF0 (init, 308 bytes; it registers the `fe_*` natives through 0x102893A0 /
  0x10280020 / 0x1036BA70 and calls `engine::LuaScriptManager::AddFunction` / `SetOwner`).
- **path unit**: 0x10864CF0 / 0x10864D80 / 0x10864DE0 / 0x10864E40 / 0x10864E50 (1-byte `ret`) and 0x10864DD0 /
  0x10864EC0 (`ret 8`) - vtable fillers or kept copies of header-defined members, not writable source; 0x10864D90
  (kept copy of the `BaseClassCasterImpl<IPathBehaviour, SplineBehaviour>` ctor) and 0x10864FA0 (its `IsDerived`);
  0x10864DA0 (`engine::PatrolPoint` ctor/dtor: vtable 0x10E7335C at +0 and `container::String::vftable` at +0x1C);
  0x10864DB0 / 0x10864EA0 (`GetScriptManager()->Unregister(&static)` for 0x11315C98 / 0x11315C9C); 0x10864DF0
  (`engine::SplineCV` ctor: vtable 0x10E73364, seven floats at +4, a flag at +0x20) and 0x10864E30 (its vtable reset);
  0x10864E60 (`dynamic_cast<SplineBehaviour*>(GetGameObject(FindGameObject(name, "")))`); 0x10864ED0
  (0x10864ED0 and the `container::ArrayDynamic<T>` members 0x10864EE0 - 0x10864F90 and 0x10864FD0 are inline
  template members - annotate them only if the instantiation can be forced out of line).
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
  whose `this` is a dummy empty object, `ScratchStackFrame` for the mark / release).
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

## the engine tracks and the fight track factory (0x108078E0 - 0x10809000 and on): not done

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
