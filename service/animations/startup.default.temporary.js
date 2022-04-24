class Animation {
  constructor() {
    /* Tweak these parameters! */
    this.angular_momentum = 300;        // deg/s
    this.wave_length = 5;               // pixel
    this.horizontal_cutoff_initial = 1; // pixel
    this.horizontal_cutoff_speed = 30;  // pixel/s
    this.horizontal_cutoff_delay = 1;   // s
    this.radial_cutoff_speed = 4;       // pixel/s
    this.radial_cutoff_delay = 2;       // s
    this.radial_inner_cutoff_delay = 4; // s
    this.runtime = 7;                   // s

    /* Calculated parameters */
    this.start_time = new Date();
    this.angular_momentum_ms = this.angular_momentum / 1000;
    this.period_ms = 360 / this.angular_momentum_ms;
    this.phase_per_pixel = -360 / this.wave_length;
    this.horizontal_cutoff_speed_ms = this.horizontal_cutoff_speed / 1000;
    this.horizontal_cutoff_delay_ms = this.horizontal_cutoff_delay * 1000;
    this.radial_cutoff_speed_ms = this.radial_cutoff_speed / 1000;
    this.radial_cutoff_delay_ms = this.radial_cutoff_delay * 1000;
    this.radial_inner_cutoff_delay_ms = this.radial_inner_cutoff_delay * 1000;
    this.runtime_ms = this.runtime * 1000;
  }

  update (params) {
    let delta_ms = params.current_frame_time - this.start_time;
    let delta_period_ms = delta_ms % this.period_ms;
    let center_x = (params.screen.resolution.width - 1) / 2;
    let center_y = (params.screen.resolution.height - 1) / 2;
    let horizontal_cutoff = Math.max(this.horizontal_cutoff_initial, this.horizontal_cutoff_speed_ms * (delta_ms - this.horizontal_cutoff_delay_ms));
    let radial_outer_cutoff = this.radial_cutoff_speed_ms * (delta_ms - this.radial_cutoff_delay_ms);
    let radial_inner_cutoff = this.radial_cutoff_speed_ms * (delta_ms - this.radial_inner_cutoff_delay_ms);

    for (let x = 0; x < params.screen.resolution.width; x++) {
        for (let y = 0; y < params.screen.resolution.height; y++) {
            let distance_from_center_x = Math.abs(x - center_x);
            let distance_from_center_y = Math.abs(y - center_y);
            let distance_from_center = Math.sqrt(Math.pow(distance_from_center_x, 2) + Math.pow(distance_from_center_y, 2));
            let phase = distance_from_center * this.phase_per_pixel + delta_period_ms * this.angular_momentum_ms;
            let color = params.libs.chroma.hsl(phase % 360, 1, 0.1);

            let is_in_horizontal_beam = distance_from_center_y < 1 && distance_from_center_x < horizontal_cutoff && distance_from_center > radial_inner_cutoff;
            let is_in_radial_beam = radial_outer_cutoff > distance_from_center && distance_from_center > radial_inner_cutoff;
            if (is_in_horizontal_beam || is_in_radial_beam) {
              params.screen.setPixel(x, y, color.hex('rgb'));
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
