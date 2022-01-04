class Animation {
  constructor() {
    this.color = '#090909';
    this.x = 0;
    this.y = 0;
  }

  update (ctx) {
    this.x++;
    if (this.x === 8){
      this.x = 0;
      this.y++;
    }
    if (this.y === 8) {
      this.y = 0;
      if (this.color === '#090909') {
        this.color = 'black';
      } else {
        this.color = '#090909';
      }
    }

    ctx.screen.setPixel(this.x, this.y, this.color);
    ctx.screen.draw();

    var next = ctx.current_frame_time;
    next.setMilliseconds(next.getMilliseconds() + 100);
    return next;
  }
}
