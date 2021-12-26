class Animation {
  #color = '#090909';
  #x = 0;
  #y = 0;

  update (ctx) {
    ctx.screen.setPixel(this.#x, this.#y, this.#color);
    ctx.screen.setPixel(0, 0, 'red');
    ctx.screen.setPixel(2, 5, 'green');
    ctx.screen.setPixel(6, 6, 'blue');
    ctx.screen.draw();

    this.#x++;
    if (this.#x === 8){
      this.#x = 0;
      this.#y++;
    }
    if (this.#y === 8) {
      this.#y = 0;
      if (this.#color === '#090909') {
        this.#color = 'black';
      } else {
        this.#color = '#090909';
      }
    }

    var next = ctx.current_frame_time;
    next.setMilliseconds(next.getMilliseconds() + 100);
    return next;
  }
}
