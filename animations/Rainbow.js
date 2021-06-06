(function (params) {
    let delta_ms = (params.current_frame_time - start_time)
                    % period_ms;

    for (let x = 0; x < screen.resolution.width; x++) {
        for (let y = 0; y < screen.resolution.height; y++) {
            let phase = x * phase_factor_x +
                        y * phase_factor_y +
                        delta_ms * angular_momentum_ms;
            let color = chroma.hsl(phase % 360, 1, 0.1);
            screen.setPixel(x, y, color.hex('rgb'));
        }
    }
    screen.draw();

    var next = params.current_frame_time;
    next.setMilliseconds(next.getMilliseconds() + 50);
    return next;
})

/* Tweak these parameters! */
const angular_momentum = 180; // deg/s
const wave_length = 8; // pixels
const wave_angle = 45; // degrees from north

/* Calculated parameters */
const start_time = new Date();
const angular_momentum_ms = angular_momentum / 1000;
const period_ms = 360 / angular_momentum_ms;
const wave_angle_radians = wave_angle * Math.PI / 180;
const phase_per_pixel = 360 / wave_length;
const phase_factor_x = phase_per_pixel * -Math.sin(wave_angle_radians);
const phase_factor_y = phase_per_pixel * -Math.cos(wave_angle_radians);
