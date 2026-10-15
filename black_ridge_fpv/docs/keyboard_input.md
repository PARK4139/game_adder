# Keyboard input checkpoint

Issue: flight/keyboard-input/a78b16c0. This is an input diagnostic, not flight physics.

| Axis | Positive | Negative |
|---|---|---|
| Throttle command | Up | Down |
| Pitch command | W | S |
| Roll command | D | A |
| Yaw command | Right | Left |

Enhanced Input builds the four Axis1D actions and their mapping context from C++; no external input assets or controller are required. Opposing keys accumulate to zero. Completed/canceled actions clear their axis. Each raw command is clamped to [-1,1]; the device-independent state approaches it with an exponential response rate of 8 per second. Release returns to neutral. In this checkpoint throttle is a signed command, not yet persistent motor power; the flight-physics issue defines thrust behavior.

After building and creating FlightTest, run launch_input_check.cmd. The two overlay lines display the current smoothed values. The diagnostic pawn remains stationary. Runtime logs prefixed a78b16c0 record each axis transition and samples in throttle,pitch,roll,yaw order. End the window with Alt+F4.

Verification requires all eight keys, release to zero, multi-axis input, opposite-key cancellation and loss of viewport focus. Preserve raw runtime logs and timing calculations in the issue's canonical evidence directory. The automation response test checks smoothing at 30/120 Hz and release behavior; it does not replace the runtime keyboard-path check.

References: https://dev.epicgames.com/documentation/en-us/unreal-engine/enhanced-input-in-unreal-engine
