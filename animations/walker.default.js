(function (params) {
    screen.setPixel(x, y, color);
    screen.setPixel(0, 0, 'red');
    screen.setPixel(2, 5, 'green');
    screen.setPixel(6, 6, 'blue');
    screen.draw();

    x++
    if (x === 8){
      x = 0
      y++
    }
    if (y === 8) {
      y = 0
      if (color === '#090909') {
        color = 'black'
      } else {
        color = '#090909'
      }
    }

    var next = params.current_frame_time;
    next.setMilliseconds(next.getMilliseconds() + 100);
    return next;
})
var color = '#090909'
var x = 0
var y = 0
