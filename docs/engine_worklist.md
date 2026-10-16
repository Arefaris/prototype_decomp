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

## engine/fmv/fmvsubtitlemanager.cpp (0x108C04E0 - 0x108C0FE0): 38 functions match, 0 nonmatching

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

Not done (11 functions):

- 0x108C04E0 (20 bytes): `StringSomething(a, b, 0)`, a forwarder into 0x1060F1B0, which builds a
  `container::StringLiteral` (vftable 0x10E0D5FC) on the stack and calls 0x1060EBA0.
- 0x108C0590 `container::StringC<256>::StringC(const StringC&)` (52 bytes): the copy constructor, a kept copy.
  `container::StringC` in `code/container/string.h` has no copy constructor yet.
- 0x108C05D0 (4 bytes): `container::StringC<256>::Data()` — emitted only if the class's vftable is, which needs a
  use of StringC<256> in this unit (0x108C0BB0 has it).
- 0x108C0650 (3 bytes, `mov eax, ecx`), 0x108C0660 / 0x108C06C0 / 0x108C07D0 (1 byte, `ret`): four functions of
  classes the unit does not otherwise show.
- 0x108C0730 (23 bytes): a second copy of the array's `Size()`, identical to 0x108C0630; the two cannot be told
  apart without knowing the second owner.
- 0x108C0880 (3 bytes, `mov eax, [ecx]`): a `begin` accessor of an unknown class.
- 0x108C0BB0 (287 bytes): the unit's string helper — it builds a StringC<256> from a name, searches it with
  0x1060F460 for two separators, and copies the part between them out.
- 0x108C0CD0 (210 bytes) `FmvSubtitleManager::Update(float)`: understood (the loop walks the elements,
  creates the text object through 0x10877110 when start <= time < end and destroys it through 0x10876B70 when the
  interval has passed, both on the object the global at 0x11316A58 points at, with the two 8-byte globals at
  0x11316A70 / 0x11316A78 as parameters) but not written: the text object's class and those three globals belong
  to another unit and their initial values are unknown.

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

## pure3d/src/context.cpp (0x1070ED50 - 0x10710930): 22 functions match, 4 nonmatching, the rest not done

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
| 0x107108A0 Shutdown | NONMATCHING | the engine keeps the context in esi across `~Context()` and passes the assert's condition register as the report's last argument; ours reloads the global and pushes the constant, 86 % |
| 0x1070F5C0 AllocRenderParams | NONMATCHING | the engine walks the pool with a running pointer and a signed count; ours indexes it, 6 % |
| 0x1070F600 FreeRenderParams | NONMATCHING | as AllocRenderParams, 6 % |
| 0x1070F650 UpdateRenderParams | NONMATCHING | the engine keeps the pool's begin in a register, ours reloads it, 10 % |

Not done: the constructor 0x107103E0 (673 bytes) and the destructor 0x107106A0 (336 bytes) - both need the frame's
many subsystems named first (they call 0x106dde80, 0x1061bbc0 / 0x1061b4c0 / 0x1061b530 / 0x1061b660 (the display),
0x1073e1d0, 0x107063a0, 0x1073e2c0, 0x1073e2e0, 0x1071f7d0, 0x10716830, 0x1073b790, 0x10754560, 0x10755120,
0x1074d770, 0x1073e260, 0x107265e0 and the `pure3d::RefCounted` objects 0x10751a00 makes). The functions of the
wrapped drawable helper's neighbours (0x10710110 = a `+0x10` this-adjusting thunk to 0x106E2AA0) and the render
parameters' pools are the same story.

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

## choreo, the unit before deltatransform.cpp (0x1094C810 - 0x1094D720): 3 functions match, 0 NONMATCHING, 50 not done

Source in `choreo/src/partitiondriver.cpp` (file name guessed; `choreo::AnimationBlendDriver`'s destructor 0x1094D290
destroys fifteen 0x2C-byte clip entries from +0x3C, so the unit is the one that builds and drives the drivers that
partition the pose). Matched: `PartitionDriver::~PartitionDriver` 0x1094D430 (releases the pose through its vftable),
`CoversRoot` 0x1094D4B0 and `Unknown1094D4C0` 0x1094D4C0 (whether the clip is at rest against the pose).

The unit is the one that builds and drives `choreo::PartitionDriver` and `choreo::AnimationBlendDriver` (RTTI
0x111EBF84 / 0x111EC030): the driver of one step of an animation, a 15-slot table of 0x2C-byte entries at +0x3C, the
clip lengths and rates (0x1094C850, 0x1094CEA0, 0x1094CEF0), the partition bit-set indexing and the blends. Nothing
is written up yet. What the rootdriver unit has since recovered (the classes are laid out in
`src/code/choreo/{rootdriver,puppet}.h` now):

- `choreo::PartitionDriver` (0x38 bytes) = `Driver` (0x1C: vptr, an 8-byte core::Name at +4, +0xC, an int at +0x10,
  the type at +0x14, the flags byte at +0x18) plus `mFirstJoint +0x20`, `mLastJoint +0x24`, `mPose +0x28`,
  `mJoint +0x2C`, `mJointMask +0x30`, `+0x34`. Its vftable is 0x10E8BC84, six slots: 0x1094D690 the bind override,
  0x109496F0 inherited, 0x1094B100 / 0x1094B110 the two joint getters, `??_G` 0x1094D550 and 0x1094D4B0
  `CoversRoot` (`mFirstJoint == 0`); the destructor is 0x1094D430 (releases the object at +0x28 through its
  vftable slot 1, then `~Driver`), not 0x1094D550.
- 0x1094D690 takes a `DriverInfo` (`{ unknown0[0xC], void* mPose +0xC }`), assigns it with 0x1094D4F0
  (`AssignRefCounted`), looks the joint up by name through 0x1094D630 -> `0x106DDC80(Pose*, const core::Name&)`
  (returns the 0x18-byte joint whose `core::Name` is at +8) and stores it with 0x1094D570 (the joint at +0x2C, its
  mask at +0x30, then a scan of the mask for the first and last joint of the range). 0x1094D4C0 returns whether the
  clip is at rest against the pose: `!(binding.mSource && mPose && binding.mClip.Unknown10952390(mJointMask))`.
- `choreo::AnimationBlendDriver`'s vftable is 0x10E8BB64: slot 0 0x1094CB50, slot 1 0x1094CB20, slots 2/3 inherited,
  `??_G` 0x1094D3C0, slot 5 inherited. Its own members start after the 0x38 bytes of PartitionDriver.
- The clip class (`choreo::AnimationClip`, 0x18 bytes: a channel pointer +0, the duration in frames +4, the rate +8,
  +0xC, a flags byte +0x10, the animation bound to it +0x14; methods 0x10952290 destroy, 0x109522A0 set,
  0x10952310 IsSet, 0x10952320 duration, 0x10952330 rate, 0x10952380 bit 1 of the flags, 0x10952390 whether the
  animation drives any joint of a mask, 0x10952480 the animation) and the two blend nodes of the job
  (`choreo::PoseBlendNode`, 0x70 bytes, and `choreo::PoseBlendSample`, 0x20 bytes, declared in poseblendjob.h) are
  already in the choreo headers.

**The blocker to know about:** this unit's file-local helpers are called with their argument in a register the
compiler of the original chose per function (`eax`, `ecx`, `esi`), which is the behaviour of link-time code generation
(/GL), not of plain /O2: our build puts them all in `ecx`. Everything that calls such a helper is off by that one
`mov`. If a later session finds a way to reproduce it, the twenty setters come with it.

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

## pure3d/texture (texture/src, unit 0x10729AE0 - 0x1072B7F0), started: 4 match, 3 NONMATCHING, 2 not done

The texture module (`code/pure3d/texture/src/`; docs/original_tree.md has `bmp.cpp` there, this unit's file name is
a guess from it). One unit holds `pure3d::Texture`, the upload helpers, `pure3d::TextureLoader` and the file parsers
`pure3d::TextureParser` / `pure3d::DDSParser`; the visibility server's unit ends exactly at 0x10729AE0.

| Address | Function | Status |
|---|---|---|
| 0x10729AE0 / 0x1072A0E0 | pure3d::Texture constructor / destructor | match |
| 0x1072B420 | DDSParser::IsSupportedFormat (vftable slot 1) | match (the switch keeps its 0x20-byte jump table after the code) |
| 0x1072B470 | DDSParser::Load (slot 2) | NONMATCHING |
| 0x1072B6D0 | DDSParser::Parse (slot 3) | NONMATCHING |
| 0x1072A470 | TextureLoader::LoadObject (slot 7) | match |
| 0x1072ADB0 / 0x1072AF80 | the upload of one texture's levels | not done |

`TextureLoader::LoadObject` (0x1072A470) matches once the loader bases exist: it is slot 7 of `content::SimpleChunkHandler`
(8 slots, RTTI), which is what the loader vftables 0x10E5C1D8 and the others hold. The bases are reconstructed in
`code/content/chunkhandler.h`: `content::ObjectLoader` (6 slots: LoadObject's five plus a pure `CreateObject`) and
`content::SimpleChunkHandler` (slot 5 `CreateObject` 0x1060B780, slot 6 the chunk flags at +8 0x105FFA40, slot 7 the
pure `LoadObject`). The reader the handler hands on is `content::ChunkReader` (0x288 bytes, stream at +0x284;
0x1060BB60 constructor, 0x1060B8E0 opens a chunk, 0x1060B8A0 asks whether one is left). `TextureLoader`'s signature is
`LoadObject(core::IRefCount** object, ObjectName* name, ChunkReader* reader, int flags)` — the object output is an
`IRefCount**` because a texture is a `pure3d::Entity`, not a `LoadObject`. Its workhorse 0x1072A1E0 takes
`(ChunkReader*, bool flag, int unknown)` and returns the `Texture*`. The class declares its destructor first and does
not define it, so the vftable stays with the engine's copy of the unit.

NONMATCHING:

- 0x1072B470 DDSParser::Load and 0x1072B6D0 DDSParser::Parse: this half of the unit is compiled with link-time code
  generation. The reader at 0x1072AB40 takes its stream in **eax** and the 0x35-byte descriptor it fills in **esi**,
  the header decoder at 0x1072B600 takes the decoded header in **esi** and one of the loader's arguments in **eax**,
  and the predicates 0x1072A530 and 0x1072AD80/0x1072A540 take their argument in **eax** and answer in **eax**. A
  caller has to set those registers itself, which no C++ declaration produces. The bodies under `#ifdef NONMATCHING`
  in `texture.cpp` record the reconstruction.

Not done:

- 0x1072A470 TextureLoader::LoadObject: `TextureLoader`'s vftable has 8 slots, so the class needs its
  `content::SimpleChunkHandler` and `content::ObjectLoader` bases, and neither unit is reconstructed. Its arguments
  are the inventory to search, an out texture, an out name and the flag the finder takes (the callee is 0x1072A1E0).
- 0x1072ADB0 and 0x1072AF80 (the per-level upload, and the resize path that calls 0x1072AB40/0x1072A540) take extra
  parameters in eax/esi like the two above and have no class in the unit's symbols. The second session did not
  retry this unit: what it needs is those helpers reconstructed in texture.cpp as `static` file-local functions
  (the trick that took choreo/deltatransform.cpp from 7 to 25 matches), since a helper that takes its argument in
  eax/esi/edi is file-local in the original.

Renames this unit made: `pure3d::TextureUploader` (a guess of the render units) is `pure3d::DDSParser` — the
constructor 0x1072B3D0 installs 0x10E5C2C8, which rtti.tsv names `.?AVDDSParser@pure3d@@`. engine/render/async/
private/drawable.cpp's DoLoadTexture (0x107EAC90) was updated and still matches.

Matching notes:

- `pure3d::Texture`'s own vftable exists although the class declares no new virtual: it overrides the destructor
  (`virtual ~Texture();`), and an empty body still emits the `mov [ecx], ??_7Texture` store the engine's has.
- `pure3d::TextureInfo` (what `Texture` keeps at +0x10) is reference-counted: the destructor releases it through the
  out-of-line `core::SafeRelease<TextureInfo>` the unit keeps at 0x1061CA90 (`if (p) { p->Release(); p = 0; }`).
- An empty 4-argument switch over a 24-value range (5 - 0x1C) comes out as the engine's byte index table feeding a
  two-entry jump table; the 8 table bytes after the code are part of the compared function.


## pure3d primitives: Mesh (src/mesh.cpp, 0x10707280 - 0x10707330), started

Mesh overrides slot 3 (`Draw`, 0x10707280, 5 arguments) and slot 7 (`FillBatch`, 0x10707330, 3 arguments) of
`Primitive` (whose layout in primitive.h is right: `LockableRefCounted` is 0xC bytes, so the flags sit at +0xC, the
type at +0x14 and the binding source at +0x18; Mesh's own members start at +0x1C). Matched:

- **The draw descriptor** is `pure3d::PrimDrawDesc` (0x54 bytes, `primstream.h`). The engine has three constructors:
  0x10611CB0 (8 arguments, the one `PrimStream::End` uses), 0x10611C30 (9, the one `Mesh::Draw` and `Skin::Draw` use)
  and 0x10611DC0 (10, the one `GpuSkin::Draw` uses); all three are declarations here, mapped in symbols.txt, and
  their argument orders differ. Map for the 9-argument one: `(void* format, const math::Matrix* world, int count,
  void** parts, PrimGroupList* list, int a, int b, int c, int d)`. The device call is `pddi->DrawPrimitive(shader,
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
- 0x1072DEC0 `GpuSkinState::GetBuffer` matches; 0x1072DF10 `GpuSkin::Draw` is NONMATCHING: it matches only with a
  0x54-byte `PrimDrawDesc`, while `PrimStream::End` (0x106F3630) needs the 0x4C one, so the descriptor the third
  constructor (0x10611DC0) fills is a larger type not recovered yet (the new unit
  `src/code/pure3d/atg4/platform/win32/gpuskin.cpp`). The gpu skin's `GpuSkinState` keeps a buffer pointer at +0x1C
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
`PrimGroupLoader`'s layout, read off its constructor and destructor: a reference-counted group list at +8 (released by
`core::SafeRelease`, 0x102CD490), an int at +0xC, three flags at +0x10 - +0x12 (the second true), an int at +0x14 and
the pairs +0x18 / +0x1C (both -1), +0x20, +0x24, +0x28.

NONMATCHING:

- 0x10B8BD30 `PrimGroupLoader::PrimGroupLoader`: the engine's copy keeps the vftable store of the base constructor it
  inlines (`mov [eax], 0x10DA05B0`, RefCounted's) between the count store and the class's own
  (`mov [eax], 0x10EAF644`) — 57 bytes. Our compiler drops that store from every derived constructor; the same shape
  compiled in this unit (three levels, the base constructor in the class body, out of line, `__forceinline`, with an
  initialiser list, with a user destructor) always comes out 6 bytes shorter, 27.5 %. `pure3d::Entity`'s constructor
  (0x1072D4B0) has the same pair of stores, so this is a property of the engine's build, not of the source.

Not done in the geometry range (each is 1500 - 2300 bytes and needs its loader class laid out first; the unit's
helpers are the ones the asserts name):

- 0x10B9C3E0 `GeometryLoader::LoadObject` (2232), 0x10B90CA0 `PolySkinLoader::LoadObject` (1575), 0x10B91410
  `CompositeDrawableLoader::LoadObject` (2232), 0x10B90A70 (130, a shared call of the mesh and skin loaders: it
  tests 0x10B8F1C0, then dispatches to 0x10B8FFE0 / 0x10B8F400 / 0x10B8DFF0 and releases the loader's list at +8
  through `core::SafeRelease` 0x102CD490).

Not done in the shader/palette range: 0x10706960 `ShaderLoader::LoadObject` (2239), 0x10B96280
`NewShaderLoader::LoadObject` (1759), 0x10B95780 `ShaderTemplateLoader::LoadObject` (1552), 0x106DE090
`SkeletonLoader::LoadObject` (2234), 0x1067F4D0 `ravenphysics::PhysicsObjectLoader::LoadObject` (761).

- 0x102A6140 `proto::ShaderPalette`'s scalar deleting destructor (`??_GShaderPalette@proto@@UAEPAXI@Z`, 30 bytes)
  is compiler-generated: it calls `??1ShaderPalette` (0x102A60B0, 107 bytes, which walks and frees the two
  `container::ArrayDynamic` members at +8 and +0x18 and restores the `content::MetaLoadObject` vftable 0x10D96DB8)
  and then `content::LoadObject::operator delete` (0x105FE720). Counting it needs the class and its destructor
  reconstructed first, in `code/proto/shaders/`; the annotation itself can be written the way
  `engine/physics/physicsmanager.cpp` annotates eight generated `??_G` bodies (a block of `// FUNCTION: ENGINE`
  lines with no definition under it).
- 0x1072E3E0 `GpuSkin::GpuSkin` (259 bytes): its shape is read off (base `Primitive::Primitive(0x4000)` 0x106F2F20,
  the vftable 0x10E5CFA0, the word at +0x1C from the third argument, `ShaderParameters` at +0x20, +0x140 / +0x15C -
  +0x164 / +0x16C initialised, the parameters copied in, a device buffer made through the global at 0x1127F358 with
  0x1061B600 (the second argument's count) and 0x1061B660, then a walk over the copied parameters comparing their
  names with the globals at 0x1127F1B8 / 0x1127F1DC and setting flags 6 / 7 through 0x102CC900 on the primitive's
  flag word at +0xC), but none of those seven callees is named yet.

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
  0x10DEA3CC) keeps the last four dents in a 0x84-byte ring at +4: the buffer runs from the ring's own address and
  its `end` pointer sits at +0x80. A dent is 0x20 bytes - a `math::Vector`, then five floats of which +0x10 and
  +0x1C are zero.
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

- `0x104E3840` (2354 bytes, the stream slot groups): mechanical but needs the signatures of ~35 callees
  (`0x1082D550` `CreateSlotGroup` with its 3-word configuration, `core::Name` construction from a literal,
  `0x10894830` / `0x10894850`, the script manager calls, `CreateFrontend`), and the configuration of each group is a
  3-word local (size, two alignment words) whose last field is only sometimes written.
- `0x1041FA40` (2043, `proto::AmbientManager`'s constructor; the singleton is 0x11267760): the manager's layout and
  its ~30 callees are not recovered.
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
- `0x102D4920` (602, `DeformShaderBehaviour`'s vftable slot 4) and `0x102D4C50` (1097,
  `DeformShaderModifier::apply`): not read yet. Both need the behaviour's vftable emitted with its slots mapped, so
  they carry the same block as the LOD slots below.
- The `DeformShaderBehaviour` vftable is 0x10DEA3CC with 8 slots and `DeformShaderModifier` 0x10DEA3C0 (base
  `engine::render::DrawableModifier`); the behaviour's members are +0 vftable, +4 the `DentBuffer` (its `end` at
  +0x84), +0x94 a float, +0x98 the dent count, +0x9C a dirty byte and +0x9D a "bias sent" byte. The dent ring the
  update walks is at the behaviour's +0x1C, in 0x20-byte records, not the `DentBuffer` at +4.
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

Remaining, in address order: 0x1071B310 / 0x1071B490 (the two 4-bone row blends over a 0x40-byte bone record whose
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

NONMATCHING:

- 0x1071B130 SkinState::GetBoundingBox: the engine copies the box through fld/fstp; needs a user-defined
  Vector::operator=, which would change every unit (the instructions are the same, integer moves instead)
- 0x1071B170 SkinState::SetBoundingBox: same reason
- 0x1071EF00 Skin::GetBoundingBox: same reason, 40 %
- 0x1071EF40 Skin::SetBoundingBox: same reason, 52 %
- 0x1071EF80 Skin::SetCentre: the four components go through fld/fstp; needs a user-defined Vector4::operator=,
  which would change every unit, 55 %

## pure3d/pddi/src/dx9 (the Direct3D 9 back end, 0x1061B530 - 0x1062B800): started, 12 functions match

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
- `pure3d::dxTexture::~dxTexture` (0x1061CBE0), the five `ReleaseRef` copies and the layout above.
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

- 0x1061CD70 `dxTexture::Create`: register allocation, 22.7 %. The whole body is there in the engine's order (the
  scale path, the level build, the three texture kinds, the pooled surface path and the retry loop), but the engine
  keeps `usage` in `ebp` and `&this->description` in `edi` where this compiler does the opposite, and it keeps
  `(usage >> 1) & 1` as a shift where this compiler folds it into `test byte [this + 0x20], 2`. Walking the
  condition through `% 2`, a named `bool` and swapping the `pool` / `usage` declarations changes neither.
- 0x1061D010 `dxTexture::Create` from an image: register allocation, 30.3 %. Same cause: the engine keeps the level
  in `edx` and reloads it from its argument slot after every Direct3D call, this compiler caches it in a
  callee-saved register, which moves every instruction behind it.
- 0x1061C600 `dxTexture::Lock`: register allocation, 17.9 %. The checks, the three lock paths (volume box, cube
  face, the system-memory copy of a 2D texture) and the lock description handed back are all there; the register
  difference above shifts the body.
- 0x10626770 `dxIndexBuffer::Create`: register allocation, 61.3 %. The body is complete and in the engine's order
  (the two tables at 0x10E3464C / 0x110BB934, the state block at +0x1C, the pooled or device allocation and the
  retry loop), but the engine keeps the usage flags in `ebx` and the Direct3D format in `ebp` where this compiler
  swaps them, and it caches the description's usage bits (`test al, 1`) where this compiler tests the field in
  place (`test byte [eax + 8], 1`); every later instruction moves. Swapping the two declarations changes neither.
- 0x1061C400 `dxTexture::dxTexture`: scheduling, 31.0 %. Every store is there with the engine's value in the
  engine's order (the -1 / 1 group at 0x28 - 0x3C sits between the runs of zero stores), but our compiler sinks that
  group behind the whole zero run and moves the vftable store with it. Writing the statements in document order and
  in the engine's order gives the same schedule.
- 0x106266D0 `dxIndexBuffer::dxIndexBuffer`: register allocation, 64.9 %. The engine clears the state block at +0x1C
  with a zero it materialises in `eax` (`xor eax, eax` after the member's constructor call), ours reuses the zero
  the initialiser list left in `ebx`.
- 0x1062AA90 `dxPrimStream::dxPrimStream`: one relocation target, 99.5 %. The buffer pool is
  `new IDirect3DVertexBuffer9*[count]`; the engine builds it through `operator new[]` (0x107DEF70), our compiler
  through `operator new` (0x107DEF50) — the body, the array-size overflow guard included, is otherwise identical.
  (`operator new[](len)` written out drops the guard and is worse.)

Not done (each is a large function of a unit whose other members are still missing):

- `dxdefaultpoolmanager.cpp`: 0x10623860 (the D3DERR text) and 0x106238B0 (the allocation failure report) are
  **static helpers with link-time-codegen conventions** — the HRESULT arrives in `eax` resp. `edi`, which plain
  `/O2` cannot produce (the same wall as 0x107DECD0 in `enginememory.cpp`). That also blocks the four pool
  allocations 0x10624990, 0x10624A70, 0x10624B10 and 0x10624BA0, which all call 0x106238B0 that way, and the big
  restore pass 0x10623FB0. The manager itself is the singleton at 0x11276DA4: five `{begin, end, capacity}` arrays
  at +0x00, +0x10, +0x20, +0x30, +0x40 (one per texture, vertex buffer, index buffer, render target and
  depth/stencil surface, each followed by an unused word), the D3D device at +0x50 and a byte at +0x54; the lock is
  `0x11276D8C`. The pool works through the device's global at 0x11276D38 (+0x50 of the manager holds the same
  pointer), and the entries it hands out are {Width, Height, Levels, float scale, Usage, Format, texture, surface}
  for a texture (0x20 bytes), {Length, Usage, FVF, buffer, data} for a vertex buffer (0x14), {Length, Usage, Format,
  buffer} for an index buffer (0x10) and {width, float scale, bool flag, height, depth, surface} for a render
  target (0x1C).
- `dxtexture.cpp`: the texture from an image 0x1061D3A0 and the surface rebind 0x1061CA00. The creations branch on
  the texture type at +8 (1 a 2D texture, 2 a cube texture, 3 a volume texture, through the device's +0x5C / +0x64 /
  +0x60), 0x1061C600 locks a level of each kind, and 0x1061C490 lays its levels out.
- the buffer creations 0x10626350 (dxVertexBuffer::Create, 873 bytes) and 0x10626770 (dxIndexBuffer::Create),
  `dxVertexDeclaration`'s own dump 0x1062B170 and the declaration table's lookup 0x1062B5C0.
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

## Merge notes (2026-10-16)

- Not reproduced at the merge and marked NONMATCHING: 0x1082DB20 `AddTriggerPackages` (36 %), 0x102D41C0
  `DentBuffer::Push` (26 %, branch layout), 0x102DA540 `LODRenderBehaviour::UpdateFade` (30 %), 0x102DDD30 /
  0x102DDE30 `MidgroundManager::CellLoaded` / `CellUnloaded` (63 % / 62 %).
- 0x107DECD0 `GetHeapKindName` is file-local and its only caller (OnAllocFail 0x107DED20) is not reconstructed, so
  the compiler drops it: NONMATCHING until the caller exists.
- skin.cpp's `BlendRows4` / `BlendRows3` are plain functions, not `__inline`: their only caller (0x1071B9A0) is
  NONMATCHING, and an inline function nothing calls is not emitted.
