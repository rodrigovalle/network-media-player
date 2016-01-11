var screen = {
    init: function() {
        this.view = document.getElementById('screen-view');
        this.holder = document.getElementById('screen-holder');
        this.width = document.documentElement.clientWidth;

        this.touch = new Hammer(this.view);
        this.screens = this.holder.childElementCount;
        this.leftEdge = 0; // start at the first screen

        this.minDist = this.width * 0.4;
        this.minSpeed = 0.65;
        this.index = 0;

        this.bindEvents();
    },

    bindEvents: function() {
        this.touch.on('panstart', this.start.bind(this));
        this.touch.on('panmove', this.move.bind(this));
        this.touch.on('panend', this.end.bind(this));
    },

    start: function(event) {
        console.log('pan start');
        this.holder.classList.remove('animate-snap');
    },

    move: function(event) {
        console.log('pan move');
        var translate = this.leftEdge;

        // animate screen boundary resistance, else animate normally
        if((this.index==0 && event.deltaX>0) ||
           (this.index==(this.screens-1) && event.deltaX<0)) {
            var sensitivity = 75 / (Math.abs(event.deltaX) + 200);
            translate += event.deltaX * sensitivity;
        } else {
            translate += event.deltaX;
        }

        //console.log(translate);
        this.holder.style.transform =
            'translate3d(' + (translate) + 'px,0,0)';
    },

    end: function(event) {
        console.log('pan end');

        // check to see if we swipe to the next screen or not
        this.animateSnap(event.velocityX, event.deltaX);

        console.log(this.index);

        // animate
        this.holder.style.transform = 
            'translate3d(' + this.leftEdge + 'px,0,0)';
            //'translate3d(-' + this.index*this.width  + 'px,0,0)';
    },

    animateSnap: function(velocity, delta) {
        this.holder.classList.add('animate-snap');
        if(Math.abs(velocity) >= this.minSpeed ||
            Math.abs(delta) >= this.minDist) {
            // check to see what direction we move the screen in
            if(delta > 0) {
                // swipe left
                this.leftEdge += this.width;
                this.index--;
            } else {
                // swipe right
                this.leftEdge += -this.width;
                this.index++;
            }
        }
    }
}

window.onload = screen.init();

