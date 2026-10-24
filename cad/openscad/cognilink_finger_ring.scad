// =============================================================================
// CogniLink Assistive Technology - Primary Finger Ring Cradle (Standalone)
// =============================================================================
// Dedicated parametric OpenSCAD model for the primary dorsal finger ring mount.
// Designed for anatomical placement on the proximal phalanx of index/middle finger.
//
// Printing: PETG, 0.20mm layer height, 100% infill, oriented with base on bed.
// =============================================================================

/* [Finger Ring Parameters] */
// Proximal phalanx inner diameter (mm) - standard adult index/middle finger = 19-23mm
FINGER_INNER_DIAMETER = 21.0;

// Internal clearance for M5StickC snap fit (mm)
TOLERANCE = 0.30;

// Ring strap cinch width (mm) - standard silicone strap = 12mm
STRAP_WIDTH = 12.0;

// Resolution
$fn = 60;

// Dimensions
MODULE_LENGTH = 48.2;
MODULE_WIDTH  = 25.5;
WALL_THICKNESS = 1.8;
BASE_THICKNESS = 1.8;
POCKET_DEPTH = 11.0;
SNAP_LIP_DEPTH = 0.50;

cav_l = MODULE_LENGTH + 2 * TOLERANCE;
cav_w = MODULE_WIDTH  + 2 * TOLERANCE;
out_l = cav_l + 2 * WALL_THICKNESS;
out_w = cav_w + 2 * WALL_THICKNESS;
tot_h = BASE_THICKNESS + POCKET_DEPTH;

module finger_ring_cradle() {
    difference() {
        // Outer body with rounded corners
        hull() {
            r_c = 2.0;
            translate([-out_l/2 + r_c, -out_w/2 + r_c, 0]) cylinder(r=r_c, h=tot_h);
            translate([ out_l/2 - r_c, -out_w/2 + r_c, 0]) cylinder(r=r_c, h=tot_h);
            translate([-out_l/2 + r_c,  out_w/2 - r_c, 0]) cylinder(r=r_c, h=tot_h);
            translate([ out_l/2 - r_c,  out_w/2 - r_c, 0]) cylinder(r=r_c, h=tot_h);
        }

        // Inner cavity
        translate([-cav_l/2, -cav_w/2, BASE_THICKNESS])
            cube([cav_l, cav_w, POCKET_DEPTH + 1.0]);

        // USB-C port cutout (-X face)
        translate([-out_l/2 - 0.5, -6.0, BASE_THICKNESS])
            cube([WALL_THICKNESS + 1.0, 12.0, 7.0]);

        // Button B (Reset) cutout (+Y face)
        translate([0.0, cav_w/2 - 0.5, BASE_THICKNESS])
            cube([10.0, WALL_THICKNESS + 1.0, 6.0]);

        // Floor ventilation slot
        translate([-16.0, -7.0, -0.5])
            cube([32.0, 14.0, BASE_THICKNESS + 1.0]);
    }

    // Top snap-fit retention lips (+/- Y)
    translate([-cav_l/2 + 4.0, -cav_w/2, tot_h - 1.0])
        rotate([0, 90, 0])
        linear_extrude(cav_l - 8.0)
        polygon(points=[[0, 0], [1.0, 0], [1.0, SNAP_LIP_DEPTH], [0.3, SNAP_LIP_DEPTH]]);

    translate([-cav_l/2 + 4.0, cav_w/2, tot_h - 1.0])
        rotate([0, 90, 0])
        linear_extrude(cav_l - 8.0)
        polygon(points=[[0, 0], [1.0, 0], [1.0, -SNAP_LIP_DEPTH], [0.3, -SNAP_LIP_DEPTH]]);

    // Anatomical dorsal curved saddle
    r_in = FINGER_INNER_DIAMETER / 2.0;
    th = 2.2;
    r_out = r_in + th;

    difference() {
        translate([-out_l/2, 0, 0])
            rotate([0, 90, 0])
            cylinder(r=r_out, h=out_l);

        translate([-out_l/2 - 1, 0, 0])
            rotate([0, 90, 0])
            cylinder(r=r_in, h=out_l + 2);

        translate([-out_l/2 - 1, -r_out - 1, -2*r_out])
            cube([out_l + 2, 2*r_out + 2, 2*r_out]);

        translate([-out_l/2 - 1, -r_out - 1, 0.01])
            cube([out_l + 2, 2*r_out + 2, r_out]);
    }

    // Lateral ring cinch loops (+/- Y)
    loop_w = 6.0;
    slot_l = STRAP_WIDTH + 0.5;
    slot_th = 2.2;

    difference() {
        union() {
            translate([-slot_l/2 - 3, -out_w/2 - loop_w, -4.0]) cube([slot_l + 6, loop_w, 4.0]);
            translate([-slot_l/2 - 3,  out_w/2,          -4.0]) cube([slot_l + 6, loop_w, 4.0]);
        }
        translate([-slot_l/2, -out_w/2 - loop_w/2 - slot_th/2, -4.5]) cube([slot_l, slot_th, 5.0]);
        translate([-slot_l/2,  out_w/2 + loop_w/2 - slot_th/2, -4.5]) cube([slot_l, slot_th, 5.0]);
    }
}

// Render model
color([0.2, 0.7, 0.9])
    finger_ring_cradle();
