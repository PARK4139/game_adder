# Requirement sources

- User request in session `01a13448-e097-7672-b1f3-f8d351932c3e`: a photorealistic / hyperrealistic exploration game featuring one BETAFPV Meteor 75 in expansive black cliffs, black rocks and snowy mountains.
- User follow-up: implement keyboard control first; other controllers come later.
- Current conversation, 2026-10-15: separate the game from the car project, prepare a plan and register issues under pk_system common rules.
- Requirements: `../docs/requirements.md`. Execution plan: `../docs/implementation_plan.md`.
- Lifecycle authority: `../../../3rd_party/pk_system/cores/common/rules/issue/lifecycle.py`.
- Evidence authority: `../../../3rd_party/pk_system/cores/common/rules/issue_verification_artifact_location.py`.

This project-local queue uses the general-family priority table. IDs are allocated by pk_system's canonical get_issue_id() and shared SQLite registry. No external issue service is used.

