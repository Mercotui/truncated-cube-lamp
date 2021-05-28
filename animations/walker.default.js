(function (params) {
    x = (x + 1) % 8
    if (x === 7){
      y = (y + 1) % 8
    }
    if (x === 7 && y === 7) {
      if (color === 'white') {
        color = 'black'
      } else {
        color = 'white'
      }
    }

    screen.setPixel(x, y, color);
    screen.setPixel(0, 0, 'red');
    screen.setPixel(2, 5, 'green');
    screen.setPixel(6, 6, 'blue');
    screen.draw();

    var next = params.current_frame_time;
    next.setMilliseconds(next.getMilliseconds() + 100);
    return next;
})
var color = 'white'
var x = 0
var y = 0
