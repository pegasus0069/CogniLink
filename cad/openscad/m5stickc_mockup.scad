// =============================================================================
// CogniLink Assistive Technology - M5StickC Reference Mockup
// =============================================================================
// Reference 3D model of the M5Stack M5StickC development kit:
// Dimensions: 48.2 x 25.5 x 13.7 mm
// Features: 0.96" TFT LCD, Button A, Button B, USB-C port, power switch
// Used for visual fit clearance checks and CSG boolean cuts in OpenSCAD
// =============================================================================

$fn = 40;

module m5stickc_module() {
    // Main enclosure body (Orange polycarbonate)
    color([0.98, 0.45, 0.05]) {
        difference() {
            // Rounded outer body
            hull() {
                translate([-24.1 + 2, -12.75 + 2, 0]) cylinder(r=2, h=13.7);
                translate([ 24.1 - 2, -12.75 + 2, 0]) cylinder(r=2, h=13.7);
                translate([-24.1 + 2,  12.75 - 2, 0]) cylinder(r=2, h=13.7);
                translate([ 24.1 - 2,  12.75 - 2, 0]) cylinder(r=2, h=13.7);
            }
            // USB-C port cavity (-X face)
            translate([-24.2, -4.5, 2.5])
                cube([3.0, 9.0, 4.0]);
        }
    }

    // 0.96" TFT LCD Display (Black glass with active screen region)
    color([0.1, 0.1, 0.12]) {
        translate([-13.0, -8.0, 13.6])
            cube([26.0, 16.0, 0.2]);
    }
    // Active display pixel area (Deep blue / cyan backlight glow)
    color([0.0, 0.6, 0.9, 0.8]) {
        translate([-11.0, -6.5, 13.75])
            cube([22.0, 13.0, 0.1]);
    }

    // Button A (Front click button, dark grey)
    color([0.25, 0.25, 0.28]) {
        translate([15.0, -5.0, 13.6])
            cube([6.0, 10.0, 0.6]);
    }

    // Button B (Side reset button, dark grey on +Y side)
    color([0.25, 0.25, 0.28]) {
        translate([2.0, 12.6, 3.5])
            cube([8.0, 1.2, 5.0]);
    }

    // Power Switch (Red slider on -Y side)
    color([0.85, 0.15, 0.15]) {
        translate([-12.0, -13.5, 4.0])
            cube([6.0, 1.0, 4.0]);
    }

    // USB-C Metal Receptacle
    color([0.75, 0.75, 0.78]) {
        translate([-24.1, -4.2, 2.8])
            cube([2.0, 8.4, 3.4]);
    }
}

// Render preview
m5stickc_module();
