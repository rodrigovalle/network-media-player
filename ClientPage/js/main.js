/* Some super hackish code here to get this thing to work
 * TODO: use backbone.js
 */

var screen = {
    view: document.getElementById('screen-view'),
    holder: document.getElementById('screen-holder'),

    index: 0,
    width: document.documentElement.clientWidth,
    holderWidth: undefined,
    leftEdge: undefined,

    // swipe detection parameters
    minSpeed: 0.65,
    minDist: undefined,

    init: function() {
        this.touch = new Hammer(this.view);
        this.screens = this.holder.childElementCount;
        this.holderWidth = this.holder.childElementCount * this.width;
        this.leftEdge = -this.index * this.width;

        this.minDist = this.width * 0.4;

        this.bindEvents();
    },

    bindEvents: function() {
        this.touch.on('panstart', function(event) {
            screen.start(event);
        });
        this.touch.on('panmove', function(event) {
            screen.move(event);
        });
        this.touch.on('panend', function(event) {
            screen.end(event);
        });
    },

    start: function(event) {
        console.log('pan start');
        this.holder.classList.remove('animate-snap');
        //this.holder.classList.add('animate-pan');
    },

    move: function(event) {
        console.log('pan move');
        var translate = this.leftEdge+event.deltaX;
        var sensitivity = 1;

        // subtract 1 because index starts from 0
        if(this.index==0 && event.deltaX>0 ||
           this.index==(this.screens-1) && event.deltaX<0) {
            sensitivity = 75 / (event.deltaX + 200);
            translate *= sensitivity;
        }

        console.log(translate);
        this.holder.style.transform =
            'translate3d(' + (translate) + 'px,0,0)';
    },

    end: function(event) {
        console.log('pan end');
        //this.holder.classList.remove('animate-pan');
        this.holder.classList.add('animate-snap');

        // check to see if we swipe to the next screen or not
        if(Math.abs(event.velocityX) >= this.minSpeed ||
           Math.abs(event.deltaX) >= this.minDist) {
            // check to see what direction we move the screen in
            if(event.deltaX > 0) {
                // swipe left
                this.leftEdge += this.width;
                this.index--;
            } else {
                // swipe right
                this.leftEdge += -this.width;
                this.index++;
            }
        }

        console.log(this.index);

        // animate
        this.holder.style.transform = 
            'translate3d(' + this.leftEdge + 'px,0,0)';
    }
}

window.onload = screen.init();

