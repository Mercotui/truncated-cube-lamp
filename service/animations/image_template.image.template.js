class Animation {
  constructor() {
    this.pixels = [["#000", "#000", "#000", "#000", "#000", "#000", "#000", "#000"], ["#000", "#000", "#000", "#000", "#000", "#000", "#000", "#000"], ["#000", "#000", "#000", "#000", "#000", "#000", "#000", "#000"], ["#000", "#000", "#000", "#000", "#000", "#000", "#000", "#000"], ["#000", "#000", "#000", "#000", "#000", "#000", "#000", "#000"], ["#000", "#000", "#000", "#000", "#000", "#000", "#000", "#000"], ["#000", "#000", "#000", "#000", "#000", "#000", "#000", "#000"], ["#000", "#000", "#000", "#000", "#000", "#000", "#000", "#000"]];
    this.resolution_x = 8;
    this.resolution_y = 8;
  }

  update (ctx) {
    for (var x = 0; x < this.resolution_x; x++){
      for (var y = 0; y < this.resolution_y; y++){
        ctx.screen.setPixel(x, y, this.pixels[x][y]);
      }
    }
    ctx.screen.draw();
    return undefined;
  }
}
