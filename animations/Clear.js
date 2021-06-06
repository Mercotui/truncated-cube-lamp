(function (params) {
    for (let x = 0; x < screen.resolution.width; x++) {
        for (let y = 0; y < screen.resolution.height; y++) {
            screen.setPixel(x, y, 'black');
        }
    }
    screen.draw();

    return undefined;
})
