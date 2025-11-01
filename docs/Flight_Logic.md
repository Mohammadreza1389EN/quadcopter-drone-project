🔹 PID in MultiWii

MultiWii is an open-source flight control system for multirotors. It uses sensor data + PID algorithm to stabilize the drone in real-time.

1️⃣ PID Concept

PID stands for Proportional – Integral – Derivative. It’s a control loop that corrects the drone’s attitude (angles) by calculating errors.

P – Proportional:

Measures the instantaneous error: error = target angle - actual angle.

Output: P_out = Kp * error

Effect: Quick correction.

⚠️ High Kp → oscillation, low Kp → slow response.

I – Integral:

Sums cumulative error over time.

Output: I_out = Ki * ∑error

Effect: Corrects persistent drift or offset.

⚠️ High Ki → overshoot or long-term oscillation.

D – Derivative:

Reacts to rate of change of error.

Output: D_out = Kd * (dError/dt)

Effect: Dampens oscillations, prevents overshoot.

⚠️ High Kd → too sensitive to sensor noise.

2️⃣ PID in MultiWii

MultiWii applies PID independently to each axis:

Roll – Left/Right tilt

Pitch – Forward/Backward tilt

Yaw – Rotation around vertical axis

Formula for each axis:

PID_output = (Kp * error) + (Ki * integral) + (Kd * derivative)


PID output is applied to motor speeds (PWM) to correct orientation.

Motors work in opposing pairs to achieve stabilization (e.g., Roll adjusts left & right motors inversely).

3️⃣ PID Control Loop in MultiWii

Sensors (IMU / MPU6050) read current angles and angular rates.

Calculate angle error: error = setpoint – measured.

Compute PID outputs for Roll, Pitch, Yaw.

Apply outputs to motors → drone stabilizes.

Loop runs hundreds of times per second for real-time stabilization.

4️⃣ Advanced Notes

PID Tuning is critical before flight.

MultiWii often uses two-level PID:

Angle PID – slower, stabilizes the overall angle.

Rate PID – faster, controls angular velocity.

Typical tuning: adjust Rate PID first, then Angle PID.

Correct PID tuning prevents overshoot, oscillation, and drift, giving smooth, stable flight.