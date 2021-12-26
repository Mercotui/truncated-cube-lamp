class Animation {
  update (ctx) {
      for (let x = 0; x < ctx.screen.resolution.width; x++) {
        for (let y = 0; y < ctx.screen.resolution.height; y++) {
          ctx.screen.setPixel(x, y, 'black');
        }
      }
      ctx.screen.draw();

      return undefined;
  }
}
