class Animation {
  #dice_representations = {
    1: [[0,0,0,0,0,0,0,0], [0,0,0,0,0,0,0,0], [0,0,0,0,0,0,0,0], [0,0,0,1,1,0,0,0],
        [0,0,0,1,1,0,0,0], [0,0,0,0,0,0,0,0], [0,0,0,0,0,0,0,0], [0,0,0,0,0,0,0,0]],
    2: [[0,0,0,0,0,0,0,0], [0,1,1,0,0,0,0,0], [0,1,1,0,0,0,0,0], [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0], [0,0,0,0,0,1,1,0], [0,0,0,0,0,1,1,0], [0,0,0,0,0,0,0,0]],
    3: [[1,1,0,0,0,0,0,0], [1,1,0,0,0,0,0,0], [0,0,0,0,0,0,0,0], [0,0,0,1,1,0,0,0],
        [0,0,0,1,1,0,0,0], [0,0,0,0,0,0,0,0], [0,0,0,0,0,0,1,1], [0,0,0,0,0,0,1,1]],
    4: [[0,0,0,0,0,0,0,0], [0,1,1,0,0,1,1,0], [0,1,1,0,0,1,1,0], [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0], [0,1,1,0,0,1,1,0], [0,1,1,0,0,1,1,0], [0,0,0,0,0,0,0,0]],
    5: [[1,1,0,0,0,0,1,1], [1,1,0,0,0,0,1,1], [0,0,0,0,0,0,0,0], [0,0,0,1,1,0,0,0],
        [0,0,0,1,1,0,0,0], [0,0,0,0,0,0,0,0], [1,1,0,0,0,0,1,1], [1,1,0,0,0,0,1,1]],
    6: [[0,0,0,0,0,0,0,0], [1,1,0,1,1,0,1,1], [1,1,0,1,1,0,1,1], [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0], [1,1,0,1,1,0,1,1], [1,1,0,1,1,0,1,1], [0,0,0,0,0,0,0,0]],
  };

  // public domain rando.js
  rando(a,b,e){var g=function(f){return"undefined"===typeof f},k=function(f){return"number"===typeof f&&!isNaN(f)},d=function(f){return!g(f)&&null!==f&&f.constructor===Array},c=function(){try{for(var f,q=[],r;30>(r="."+q.join("")).length;){f=(window.crypto||window.msCrypto).getRandomValues(new Uint32Array(5));for(var p=0;p<f.length;p++){var t=4E9>f[p]?f[p].toString().slice(1):"";0<t.length&&(q[q.length]=t)}}return Number(r)}catch(v){return Math.random()}};try{if(null!==a&&null!==b&&null!==
e){if(g(a))return c();if(window.jQuery&&a instanceof jQuery&&g(b)){if(0==a.length)return!1;var n=rando(0,a.length-1);return{index:n,value:a.eq(n)}}if(k(a)&&k(b)&&"string"===typeof e&&"float"==e.toLowerCase().trim()){if(a>b){var m=b;b=a;a=m}return c()*(b-a)+a}if(d(a)&&0<a.length&&g(b)){var l=c()*a.length<<0;return{index:l,value:a[l]}}if("object"===typeof a&&g(b)){l=a;var h=Object.keys(l);if(0<h.length){var u=h[h.length*c()<<0];return{key:u,value:l[u]}}}if((!0===a&&!1===b||!1===a&&!0===b)&&g(e))return.5>
rando();if(k(a)&&g(b))return 0<=a?rando(0,a):rando(a,0);if(k(a)&&"string"===typeof b&&"float"==b.toLowerCase().trim()&&g(e))return 0<=a?rando(0,a,"float"):rando(a,0,"float");if(k(a)&&k(b)&&g(e))return a>b&&(m=b,b=a,a=m),a=Math.floor(a),b=Math.floor(b),Math.floor(c()*(b-a+1)+a);if("string"===typeof a&&0<a.length&&g(b))return a.charAt(rando(0,a.length-1))}return!1}catch(f){return!1}}

  update (ctx) {
    const dice_roll = this.rando(1, 6);
    const dice_representation = this.#dice_representations[dice_roll];

    for (let x = 0; x < 8; x++) {
      for (let y = 0; y < 8; y++) {
        if (dice_representation[y][x]){
          ctx.screen.setPixel(x, y, '#090909');
        } else {
          ctx.screen.setPixel(x, y, 'black');
        }
      }
    }
    ctx.screen.draw();

    return undefined;
  }
}
