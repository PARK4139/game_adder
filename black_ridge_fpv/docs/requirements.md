# Requirements and acceptance units

Created: 2026-10-15. Source provenance: ../issues/sources.md.

FR-001, FR-002, FR-008 and FR-010 derive from user product direction. The other units and numeric targets are proposed first-demo implementation baselines, not historical user quotations. UE 5.8 is selected; the exact installed hotfix and Meteor 75 variant remain unverified.

| FR | Requirement | AC | Acceptance |
|---|---|---|---|
| FR-001 | Keep a separately launchable FPV game project | AC-001 | Record engine/version and decision rationale; launch an empty level from documented steps with no car-project dependencies. |
| FR-002 | Start with keyboard control | AC-002 | Keyboard independently drives throttle, pitch, roll and yaw in [-1,1] (throttle may use [0,1]); record press/release values, smoothing and selected bindings without requiring a controller. |
| FR-003 | Fly one drone using thrust and attitude | AC-003 | A keyboard run demonstrates takeoff, forward flight, left/right turns and controlled landing; input, transforms and velocities demonstrate gravity and attitude-dependent thrust. |
| FR-004 | Make keyboard flight approachable | AC-004 | From a tilted state, releasing attitude keys levels the drone within 3 seconds in each of 3 trials; record starting tilt, final error, configured tolerance and stabilization limits. |
| FR-005 | Respect terrain during flight | AC-005 | At the documented demo maximum speed, 5 head-on and 5 grazing contacts do not pass through test obstacles; retain pre/post-contact motion and collision configuration. |
| FR-006 | Recover quickly after collision | AC-006 | In 3 trials, R restores position, orientation and velocity to a collision-free spawn within 1 second and permits immediate flight. |
| FR-007 | Observe terrain from the drone and externally | AC-007 | Tab switches both views in 3 trials without changing drone motion; FPV stays attached and the external view permits inspection of nearby terrain. |
| FR-008 | Explore expansive black cliffs and snowy mountains | AC-008 | A blockout has a launch area, cliff corridor, snowy ridge and landing area; a 3-minute route stays inside playable terrain and measured map extent is recorded. |
| FR-009 | Represent the specified BETAFPV Meteor 75 | AC-009 | Record the chosen variant, reference provenance, dimensions and camera angle; a proportioned representation appears in external view with no missing assets. |
| FR-010 | Present realistic black rock and snow | AC-010 | Near/mid/far route captures pass the documented visual checklist and an asset-license manifest records all third-party assets. |
| FR-011 | Measure playability on the target PC | AC-011 | For a 3-minute route at 1920x1080, average FPS >=60, 1% low >=45 and peak dedicated VRAM <=7 GiB; retain raw samples, hardware, build and settings, reporting each miss. |
| FR-012 | Deliver a reproducible first playable demo | AC-012 | A runnable build and instructions reproduce two keyboard-only runs through launch, takeoff, exploration, view switching, landing and reset without crash. |

AC-009 visual checklist: coherent scale; close-range black-rock detail; snow placement consistent with slopes; separation of near/far mountains; no missing materials, obvious placeholder surfaces or severe terrain seams on the representative route. Record reviewer judgment for each item; do not claim an objective photorealism score.

AC-011 is a provisional budget for the reported laptop GPU. Record any agreed budget change and its reason before re-verification; never silently lower a target to close an issue. Define the frame-time percentile calculation and sampling method in the measurement report.
