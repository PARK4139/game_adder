# 작업 현황과 재개 절차

기록일: 2026-10-15. 이 문서는 현재 작성된 코드와 미검증 범위를 보존하는 작업 인계 문서다. 런타임 검증 로그와 완료 증거는 이슈 관리 규칙의 외부 증거 경로에서 관리한다.

## 실행 범위와 현재 판정

사용자의 `do next issue` 요청으로 실행 기반 `367c7496`과 다음 키보드 입력 `a78b16c0`를 함께 진행했다. 두 이슈는 같은 새 게임 모듈을 빌드해야 하므로 엔진 설치 중 입력 소스를 준비하는 방식으로 묶었다. 선행 실행 기반이 PASS하기 전에는 입력 이슈를 완료 처리하지 않는다.

두 이슈 모두 `issues/working/`에 있다. 게임플레이 완료 이슈는 아직 없다. 나머지 10개 개발 이슈는 `backlog`다. 기존 `closed` 2개는 환경·Git 체크포인트 사건 기록이며, 게임 기능 완료를 의미하지 않는다.

## 엔진과 설치 상태

- 선택한 기준은 Unreal Engine 5.8이며, 마지막 런처 화면에서는 **5.8.3 설치 중 53%**로 표시됐다.
- Epic Games Launcher 설치와 계정 로그인은 진행된 것으로 확인했다. 이전 문서의 ‘로그인 대기’는 더 이상 현재 상태가 아니다.
- 이번 기록 시점에도 설치 manifest의 `InstallationList`가 비어 있고, 표준 경로에 `Engine/Build/Build.version`과 `UnrealEditor.exe`가 없다. 따라서 다운로드·설치 완료나 실제 엔진 빌드 번호를 확정하지 않는다.
- 이전 작업에서 사용자가 물리적 Esc 키로 Computer Use를 중지했다. 그 이후 UI 작업은 수행하지 않았으며, 이번 요청은 파일 기반 현황 기록과 커밋에 한정한다.

## 실행 기반 이슈 — 367c7496

준비된 파일은 `BlackRidgeFPV.uproject`, C++ 게임·에디터 Target, 모듈 Build.cs와 모듈 진입점, `Config/DefaultEngine.ini`, `Config/DefaultGame.ini`다. 프로젝트 경로는 자동차 프로젝트와 독립적이다.

- `build_editor.cmd`: UE의 Build.bat로 Development Editor를 빌드한다.
- `initialize_level.cmd`: 에디터 Python commandlet로 `scripts/initialize_level.py`를 실행한다.
- `scripts/initialize_level.py`: 빈 `/Game/Maps/FlightTest`를 생성하고 저장한다. 기존 맵이 있으면 덮어쓰지 않는다.
- `launch_editor.cmd`: 생성된 맵을 에디터로 연다.
- `scripts/resolve_engine.cmd`: 기본 UE_5.8 경로 또는 `UE_ROOT` 환경 변수를 사용한다. 엔진이 없으면 명시적으로 종료 코드 2를 반환한다.

이전 검사에서 프로젝트 JSON·Python 문법·자동차 소스 의존성 부재와 세 실행 진입점의 엔진 부재 종료 코드 2를 확인했다. 실제 UE 컴파일, 맵 생성, 에디터 두 차례 실행은 아직 확인하지 않았다. 특히 새 입력 소스가 추가된 이후의 전체 모듈은 한 번도 컴파일되지 않았다.

## 키보드 입력 이슈 — a78b16c0

| 파일 | 작성된 역할 |
|---|---|
| `Config/DefaultInput.ini` | Enhanced PlayerInput·InputComponent 선택, 포커스 상실 시 눌린 키 해제 설정 |
| `FlightInputState.h` | 장치와 분리한 스로틀·피치·롤·요 상태, 정규화 범위 제한, 지수 응답 스무딩 |
| `FlightInputPawn.h/.cpp` | 런타임 네 개 Axis1D 액션과 매핑 생성, 이벤트 수신, 눌림·해제 값 처리, 진단 카메라와 화면 표시 |
| `FlightInputGameMode.h/.cpp` | 입력 확인용 Pawn 선택 |
| `Tests/FlightInputStateTests.cpp` | 30/120Hz 응답 비교, 눌림 수렴·해제 복귀·범위 제한 자동화 테스트 소스 |
| `launch_input_check.cmd` | 입력 전용 GameMode로 창 모드 실행, `-FPVInputTrace` 활성화 |
| `docs/keyboard_input.md` | 키 배치, 입력 의미, 검증 항목 |

키 배치는 W/S 피치, D/A 롤, 오른쪽/왼쪽 방향키 요, 위/아래 방향키 스로틀 명령이다. 양·음 키를 같은 액션에 누적해 반대 키는 상쇄하도록 작성했다. Completed/Canceled 이벤트는 축을 중립으로 돌리고, 스무딩은 초당 응답률 8의 지수 함수로 작성했다.

`-FPVInputTrace`를 켜면 `a78b16c0` 식별자로 원시 목표 변화와 스무딩 샘플을 UE 로그에 남기도록 했다. 샘플 순서는 throttle,pitch,roll,yaw다. 화면에는 키 안내와 네 축 값이 표시되도록 작성했다.

이 단계의 스로틀은 [-1,1] 부호 있는 명령이며, 실제 모터 추력이나 유지되는 스로틀 설정이 아니다. Pawn은 이동하지 않는다. 비행 물리, 안정화 모드, 충돌·복귀, 산악 지형, Meteor 기체 모델은 아직 구현하지 않았다. 입력 확인용 고정 카메라는 최종 FPV/외부 관찰 시점 전환 구현이 아니다.

## 미검증 항목과 예상 확인 지점

입력 소스와 자동화 테스트는 작성만 했으며 UE 빌드·테스트 실행은 하지 못했다. 최신 엔진 헤더/API 호환성, 런타임 소유·포제션과 매핑 등록 순서, Completed/Canceled 시 값, 포커스 상실 후 중립 복귀, 화면 표시와 실제 키 처리 모두 런타임 확인이 필요하다. 정적 문서·형식 검사를 이러한 동작의 PASS로 대체하지 않는다.

## 정확한 재개 순서

1. 런처에서 UE 5.8.3 설치 완료를 확인하고 실제 `Build.version`을 기록한다. 다른 경로라면 `UE_ROOT`를 지정한다.
2. 프로젝트의 `build_editor.cmd`를 실행한다. 컴파일 오류가 나면 원인과 변경 사항을 이슈에 기록하고 수정 후 재빌드한다.
3. `initialize_level.cmd`로 빈 FlightTest 맵을 생성한다.
4. `launch_editor.cmd`로 맵을 열고 종료한 뒤 다시 열어 실행 기반 AC-001을 두 번 검증한다. 성공 증거·결과 요약을 기록한 뒤 해당 이슈만 `closed`로 이동하고 Active 행을 제거한다.
5. UE 자동화 테스트 `BlackRidgeFPV.Input.FrameRateIndependentResponse`를 실행하고 실제 결과를 보관한다.
6. `launch_input_check.cmd`를 실행해 8개 키 각각의 양·음 입력과 해제, 서로 다른 축의 동시 입력, 반대 키 상쇄, 포커스 이탈·복귀를 확인한다. 로그의 실제 목표·스무딩 값과 시간을 읽어 기록한다.
7. AC-002가 통과할 때만 입력 이슈를 `closed`로 이동하고 Active 행을 제거한다. 컴파일 성공만으로 완료하지 않는다.

현재 요청의 커밋은 미완료 작업 보존용이다. 이후 비행 물리 이슈 `7bb11510` 착수는 위 검증 이후다.

## 증거·세션·체크포인트

실행 세션: `01a13dca-3432-7f53-8804-e198f039c46f`.

- 계획 체크포인트: `f860644`.
- UE 실행 기반 체크포인트: `17dbbc9`.
- 실행 로그: `{D_TEMP}/do-issue/black_ridge_fpv/20261015-01a13dca/queue.jsonl`.
- 실행 기반 증거: `{D_TEMP}/evidence/black_ridge_fpv/verification/367c7496/` 및 같은 verification 폴더의 `E_367c7496.md`.
- 입력 증거: `{D_TEMP}/evidence/black_ridge_fpv/verification/a78b16c0/` 및 같은 verification 폴더의 `E_a78b16c0.md`.

`{D_TEMP}`는 pk_system의 canonical path constant에서 가져온 외부 임시 루트다. 프로젝트 안에 동명 폴더를 만들지 않는다.

## Git 저장 범위

소스·설정·문서·이슈·재생성 스크립트만 보관한다. 엔진, 다운로드, 빌드·캐시·Saved, 영상, 패키지, 디버그 심볼과 바이너리 에셋은 제외한다. 생성 맵과 외부 에셋을 둘 `Content/`, `Assets/`, `LocalAssets/`도 제외한다. 현재 빈 맵은 bootstrap 스크립트로 재생성한다. 향후 수작업 자산은 외부 저장 위치·출처·복원 방법을 문서화해야 한다.

Git ignore는 파일 크기 조건을 직접 표현하지 못하므로, 이번 커밋에서는 스테이징된 파일의 크기와 확장자를 별도 검사한다. 10 MiB 이상 파일을 차단하는 보수적인 확인 기준을 사용하며 현재 변경은 모두 작은 텍스트 파일이다.
