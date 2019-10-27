thickness=1.5;

difference() {
    union() {
        translate([-50,-85,0]) {
            cube([100,180,thickness]);
        }
        
        translate([-75,0,0]) {
            cube([150,30,thickness]);
        }
    }
    minkowski() {
        import("sugarskull_v1.stl");
        cube([.275,.275,.275]);
    }    
    translate([-40,-55,0]) {
        cube([80,30,thickness]);
    }
}