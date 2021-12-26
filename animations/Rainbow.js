class Animation {
  /* Tweak these parameters! */
  #angular_momentum = 180;  // deg/s
  #wave_length = 8;         // pixels
  #wave_angle = 45;         // degrees from north

  /* Calculated parameters */
  #start_time = new Date();
  #angular_momentum_ms = this.#angular_momentum / 1000;
  #period_ms = 360 / this.#angular_momentum_ms;
  #wave_angle_radians = this.#wave_angle * Math.PI / 180;
  #phase_per_pixel = 360 / this.#wave_length;
  #phase_factor_x = this.#phase_per_pixel * -Math.sin(this.#wave_angle_radians);
  #phase_factor_y = this.#phase_per_pixel * -Math.cos(this.#wave_angle_radians);

  update (params) {
    let delta_ms = (params.current_frame_time - this.#start_time)
                    % this.#period_ms;

    for (let x = 0; x < params.screen.resolution.width; x++) {
        for (let y = 0; y < params.screen.resolution.height; y++) {
            let phase = x * this.#phase_factor_x +
                        y * this.#phase_factor_y +
                        delta_ms * this.#angular_momentum_ms;
            let color = this.chroma.hsl(phase % 360, 1, 0.1);
            params.screen.setPixel(x, y, color.hex('rgb'));
        }
    }
    params.screen.draw();

    var next = params.current_frame_time;
    next.setMilliseconds(next.getMilliseconds() + 50);
    return next;
  };
}
