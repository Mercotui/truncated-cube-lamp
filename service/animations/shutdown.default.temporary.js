class Animation {
  constructor() {
    /* Tweak these parameters! */
    this.horizontal_cutoff_speed = 100;   // pixel/s
    this.radial_cutoff_speed = 8;         // pixel/s
    this.radial_inner_cutoff_delay = 0.3; // s
    this.runtime = 1;                     // s

    /* Calculated parameters */
    this.start_time = new Date();
    this.angular_momentum_ms = this.angular_momentum / 1000;
    this.period_ms = 360 / this.angular_momentum_ms;
    this.phase_per_pixel = 360 / this.wave_length;
    this.horizontal_cutoff_speed_ms = this.horizontal_cutoff_speed / 1000;
    this.radial_cutoff_speed_ms = this.radial_cutoff_speed / 1000;
    this.radial_inner_cutoff_delay_ms = this.radial_inner_cutoff_delay * 1000;
    this.runtime_ms = this.runtime * 1000;
  }

  update (params) {
    let delta_ms = params.current_frame_time - this.start_time
    let runtime_left = this.runtime_ms - delta_ms;
    let center_x = (params.screen.resolution.width - 1) / 2;
    let center_y = (params.screen.resolution.height - 1) / 2;
    let horizontal_cutoff = this.horizontal_cutoff_speed_ms * runtime_left;
    let radial_outer_cutoff = this.radial_cutoff_speed_ms * runtime_left;
    let radial_inner_cutoff = this.radial_cutoff_speed_ms * (runtime_left - this.radial_inner_cutoff_delay_ms);

    for (let x = 0; x < params.screen.resolution.width; x++) {
        for (let y = 0; y < params.screen.resolution.height; y++) {
            let distance_from_center_x = Math.abs(x - center_x);
            let distance_from_center_y = Math.abs(y - center_y);
            let distance_from_center = Math.sqrt(Math.pow(distance_from_center_x, 2) + Math.pow(distance_from_center_y, 2));

            let is_in_horizontal_beam = distance_from_center_y < 1 && distance_from_center_x < horizontal_cutoff && distance_from_center > radial_inner_cutoff;
            let is_in_radial_beam = radial_outer_cutoff > distance_from_center && distance_from_center > radial_inner_cutoff;
            if (is_in_horizontal_beam || is_in_radial_beam) {
              params.screen.setPixel(x, y, '#333');
            } else {
              params.screen.setPixel(x, y, '#000');
            }
        }
    }
    params.screen.draw();

    if (this.runtime_ms > delta_ms) {
      var next = params.current_frame_time;
      next.setMilliseconds(next.getMilliseconds() + 50);
      return next;
    } else {
      return undefined;
    }
  }
}
