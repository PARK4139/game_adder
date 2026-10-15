# Function families

Owner: `black_ridge_fpv`. Issues and implementation belong to this project.

| function family | meaning | implementation location |
|---|---|---|
| project_setup | Engine selection and reproducible project startup | Game project and launch documentation |
| flight | Keyboard input, flight physics, assistance, collision and recovery | Game input and flight components |
| camera | FPV and external observation views | Game camera components |
| environment | Traversable mountain layout and realistic black rock and snow | Levels, terrain, materials and asset records |
| vehicle | Meteor 75 reference selection and representation | Drone assets and reference records |
| diagnostics | Performance measurement and demo acceptance | Verification procedures and measurement tools |
| build_env | Engine installation and build-environment incident records | Engine setup and startup scripts |
| process | Project execution and checkpoint incident records | Issue execution and Git checkpoints |

Table order breaks ties after priority and prerequisites. Subfamilies use kebab-case.

