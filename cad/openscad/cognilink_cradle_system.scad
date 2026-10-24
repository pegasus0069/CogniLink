// =============================================================================
// CogniLink Assistive Technology - Master Parametric Cradle System
// =============================================================================
// OpenSCAD Parametric Cradle Generator supporting 6 anatomical configurations:
//   - UNIVERSAL : Flat base carrier with dual 15x2.5mm strap loops
//   - FINGER    : Dorsal proximal phalanx saddle with lateral ring cinch loops
//   - WRIST     : Broad carpal saddle with dual 20.5x2.8mm medical band slots
//   - EYEGLASS  : Tension-fit dual-jaw clip for 2.5-5.0mm spectacle frame arms
//   - HEADBAND  : Cranial curved plate with dual 26x3.0mm elastic band slots
//   - HALLUX    : Great toe saddle with distal pedal interphalangeal relief
//
// Designed for FDM printing in PETG (0.20mm layer height, 100% infill).
// Correlates with:
//   - CogniLink IEEE Journal Paper (Section IV-B, Table XI BOM, Fig. 1)
// =============================================================================

/* [Configuration & Mounting Mode] */
// Select anatomical mounting mode
MOUNT_TYPE = "FINGER"; // [UNIVERSAL: Universal Cradle, FINGER: Finger Ring Mount, WRIST: Wrist Strap Mount, EYEGLASS: Eyeglass Temple Clip, HEADBAND: Headband Mount, HALLUX: Hallux Toe Mount]

// Display M5StickC reference mockup inside cradle
SHOW_MOCKUP = false;

/* [General Dimensions & 3D Printing Tolerances] */
// M5StickC module length (mm)
MODULE_LENGTH = 48.2;
// M5StickC module width (mm)
MODULE_WIDTH  = 25.5;
// M5StickC module thickness (mm)
MODULE_HEIGHT = 13.7;

// Internal clearance per side for FDM snap-fit (mm)
TOLERANCE = 0.30;
// Wall thickness for structural rigidity (mm)
WALL_THICKNESS = 1.8;
// Base floor thickness (mm)
BASE_THICKNESS = 1.8;
// Depth of module pocket (mm) - leaves top open for screen/button access
POCKET_DEPTH = 11.0;
// Inward snap lip overhang along top edges (mm)
SNAP_LIP_DEPTH = 0.50;

/* [Anatomical Sizing Parameters] */
// Finger proximal phalanx inner diameter (mm)
FINGER_INNER_DIAMETER = 21.0;
// Wrist carpal curvature radius (mm)
WRIST_CARPAL_RADIUS = 32.0;
// Headband frontal curvature radius (mm)
HEADBAND_CRANIAL_RADIUS = 80.0;
// Hallux (great toe) inner diameter (mm)
HALLUX_INNER_DIAMETER = 26.0;
// Eyeglass temple arm clamping slot thickness (mm)
EYEGLASS_TEMPLE_THICKNESS = 3.2;

/* [Strap Loop Dimensions] */
// Finger ring strap width (mm)
STRAP_WIDTH_FINGER = 12.0;
// Wrist strap width (mm)
STRAP_WIDTH_WRIST = 20.0;
// Headband elastic width (mm)
STRAP_WIDTH_HEADBAND = 25.0;

/* [Fine Tuning] */
// Curve rendering resolution
$fn = 60;

// Calculated internal and external dimensions
cav_l = MODULE_LENGTH + 2 * TOLERANCE;
cav_w = MODULE_WIDTH  + 2 * TOLERANCE;
out_l = cav_l + 2 * WALL_THICKNESS;
out_w = cav_w + 2 * WALL_THICKNESS;
tot_h = BASE_THICKNESS + POCKET_DEPTH;

// =============================================================================
// Core Cradle Module (Universal Carrier Sleeve)
// =============================================================================

module core_cradle_sleeve() {
    difference() {
        // Outer cradle body with radiused external corners
        hull() {
            r_c = 2.0;
            translate([-out_l/2 + r_c, -out_w/2 + r_c, 0]) cylinder(r=r_c, h=tot_h);
            translate([ out_l/2 - r_c, -out_w/2 + r_c, 0]) cylinder(r=r_c, h=tot_h);
            translate([-out_l/2 + r_c,  out_w/2 - r_c, 0]) cylinder(r=r_c, h=tot_h);
            translate([ out_l/2 - r_c,  out_w/2 - r_c, 0]) cylinder(r=r_c, h=tot_h);
        }

        // Inner module pocket (Z from BASE_THICKNESS to top)
        translate([-cav_l/2, -cav_w/2, BASE_THICKNESS])
            cube([cav_l, cav_w, POCKET_DEPTH + 1.0]);

        // USB-C port cutout on -X bottom wall (allows charging & programming)
        translate([-out_l/2 - 0.5, -6.0, BASE_THICKNESS])
            cube([WALL_THICKNESS + 1.0, 12.0, 7.0]);

        // Button B (Reset) cutout on +Y lateral wall
        translate([0.0, cav_w/2 - 0.5, BASE_THICKNESS])
            cube([10.0, WALL_THICKNESS + 1.0, 6.0]);

        // Battery ventilation & mass-reduction slot in floor
        translate([-16.0, -7.0, -0.5])
            cube([32.0, 14.0, BASE_THICKNESS + 1.0]);
    }

    // Snap-fit retention lips along top long edges (+/- Y)
    // Chamfered lead-in lip for easy push-in snapping
    // Lip on -Y wall
    translate([-cav_l/2 + 4.0, -cav_w/2, tot_h - 1.0])
        rotate([0, 90, 0])
        linear_extrude(cav_l - 8.0)
        polygon(points=[[0, 0], [1.0, 0], [1.0, SNAP_LIP_DEPTH], [0.3, SNAP_LIP_DEPTH]]);

    // Lip on +Y wall
    translate([-cav_l/2 + 4.0, cav_w/2, tot_h - 1.0])
        rotate([0, 90, 0])
        linear_extrude(cav_l - 8.0)
        polygon(points=[[0, 0], [1.0, 0], [1.0, -SNAP_LIP_DEPTH], [0.3, -SNAP_LIP_DEPTH]]);
}

// =============================================================================
// Anatomical Mount Assemblies
// =============================================================================

// 1. UNIVERSAL CRADLE
module mount_universal() {
    core_cradle_sleeve();

    // Lateral flanged strap loops (+/- Y)
    flange_ext = 8.0;
    flange_th = 2.4;
    slot_l = 15.0;
    slot_w = 2.5;

    difference() {
        union() {
            // -Y Flange
            translate([-out_l/2, -out_w/2 - flange_ext, 0])
                cube([out_l, flange_ext, flange_th]);
            // +Y Flange
            translate([-out_l/2, out_w/2, 0])
                cube([out_l, flange_ext, flange_th]);
        }
        // Slots on -Y
        translate([-15.0 - slot_l/2, -out_w/2 - flange_ext/2 - slot_w/2, -0.5]) cube([slot_l, slot_w, flange_th + 1]);
        translate([ 15.0 - slot_l/2, -out_w/2 - flange_ext/2 - slot_w/2, -0.5]) cube([slot_l, slot_w, flange_th + 1]);
        // Slots on +Y
        translate([-15.0 - slot_l/2,  out_w/2 + flange_ext/2 - slot_w/2, -0.5]) cube([slot_l, slot_w, flange_th + 1]);
        translate([ 15.0 - slot_l/2,  out_w/2 + flange_ext/2 - slot_w/2, -0.5]) cube([slot_l, slot_w, flange_th + 1]);
    }
}

// 2. PRIMARY FINGER RING MOUNT
module mount_finger_ring() {
    core_cradle_sleeve();

    r_in = FINGER_INNER_DIAMETER / 2.0;
    th = 2.2;
    r_out = r_in + th;

    // Curved anatomical dorsal phalanx saddle under cradle
    difference() {
        translate([-out_l/2, 0, 0])
            rotate([0, 90, 0])
            cylinder(r=r_out, h=out_l);

        // Subtracted finger clearance cylinder
        translate([-out_l/2 - 1, 0, 0])
            rotate([0, 90, 0])
            cylinder(r=r_in, h=out_l + 2);

        // Cut off lower half
        translate([-out_l/2 - 1, -r_out - 1, -2*r_out])
            cube([out_l + 2, 2*r_out + 2, 2*r_out]);

        // Flatten top to join cradle floor
        translate([-out_l/2 - 1, -r_out - 1, 0.01])
            cube([out_l + 2, 2*r_out + 2, r_out]);
    }

    // Lateral ring strap cinch brackets (+/- Y) for 12mm silicone ring band
    loop_w = 6.0;
    slot_l = STRAP_WIDTH_FINGER + 0.5;
    slot_th = 2.2;

    difference() {
        union() {
            translate([-slot_l/2 - 3, -out_w/2 - loop_w, -4.0]) cube([slot_l + 6, loop_w, 4.0]);
            translate([-slot_l/2 - 3,  out_w/2,          -4.0]) cube([slot_l + 6, loop_w, 4.0]);
        }
        // Slots
        translate([-slot_l/2, -out_w/2 - loop_w/2 - slot_th/2, -4.5]) cube([slot_l, slot_th, 5.0]);
        translate([-slot_l/2,  out_w/2 + loop_w/2 - slot_th/2, -4.5]) cube([slot_l, slot_th, 5.0]);
    }
}

// 3. WRIST STRAP MOUNT
module mount_wrist() {
    core_cradle_sleeve();

    r_in = WRIST_CARPAL_RADIUS;
    th = 2.6;
    r_out = r_in + th;
    w_len = out_l + 6.0;
    w_width = 56.0;

    // Broad carpal saddle
    difference() {
        translate([-w_len/2, 0, 0])
            rotate([0, 90, 0])
            cylinder(r=r_out, h=w_len);

        translate([-w_len/2 - 1, 0, 0])
            rotate([0, 90, 0])
            cylinder(r=r_in, h=w_len + 2);

        translate([-w_len/2 - 1, -r_out - 1, -2*r_out])
            cube([w_len + 2, 2*r_out + 2, 2*r_out]);

        translate([-w_len/2 - 1, -r_out - 1, 0.01])
            cube([w_len + 2, 2*r_out + 2, r_out]);
    }

    // Dual 20mm wristband strap loops on -X and +X ends
    wing_len = 8.0;
    slot_w = STRAP_WIDTH_WRIST + 0.8;
    slot_th = 2.8;

    difference() {
        union() {
            translate([-w_len/2 - wing_len, -w_width/2, -3.0]) cube([wing_len, w_width, 3.0]);
            translate([ w_len/2,            -w_width/2, -3.0]) cube([wing_len, w_width, 3.0]);
        }
        translate([-w_len/2 - wing_len/2 - slot_th/2, -slot_w/2, -3.5]) cube([slot_th, slot_w, 4.0]);
        translate([ w_len/2 + wing_len/2 - slot_th/2, -slot_w/2, -3.5]) cube([slot_th, slot_w, 4.0]);
    }
}

// 4. EYEGLASS TEMPLE CLIP
module mount_eyeglass_clip() {
    core_cradle_sleeve();

    clip_len = 32.0;
    clip_gap = EYEGLASS_TEMPLE_THICKNESS;
    jaw_th = 2.0;
    clip_depth = 9.0;
    bridge_w = 4.0;

    // Lateral bridge from cradle
    translate([-clip_len/2, -out_w/2 - bridge_w, 2.0])
        cube([clip_len, bridge_w, clip_depth]);

    // Compliant J-clip channel
    y_inner = -out_w/2 - bridge_w;
    // Inner leg
    translate([-clip_len/2, y_inner - jaw_th, 0])
        cube([clip_len, jaw_th, clip_depth + 2.0]);
    // Top connecting arch
    translate([-clip_len/2, y_inner - jaw_th - clip_gap - jaw_th, clip_depth])
        cube([clip_len, clip_gap + 2*jaw_th, 2.0]);
    // Outer compliant clamping leg
    translate([-clip_len/2, y_inner - 2*jaw_th - clip_gap, 0])
        cube([clip_len, jaw_th, clip_depth + 2.0]);
    // Chamfered lead-in lip for easy sliding onto spectacles
    translate([-clip_len/2, y_inner - 2*jaw_th - clip_gap - 1.2, 0])
        cube([clip_len, 1.2, 1.8]);
}

// 5. FOREHEAD HEADBAND MOUNT
module mount_headband() {
    core_cradle_sleeve();

    r_in = HEADBAND_CRANIAL_RADIUS;
    th = 2.6;
    r_out = r_in + th;
    p_len = out_l + 10.0;
    p_width = 64.0;

    // Cranial curved contoured base
    difference() {
        translate([-p_len/2, 0, 0])
            rotate([0, 90, 0])
            cylinder(r=r_out, h=p_len);

        translate([-p_len/2 - 1, 0, 0])
            rotate([0, 90, 0])
            cylinder(r=r_in, h=p_len + 2);

        translate([-p_len/2 - 1, -r_out - 1, -2*r_out])
            cube([p_len + 2, 2*r_out + 2, 2*r_out]);

        translate([-p_len/2 - 1, -r_out - 1, 0.01])
            cube([p_len + 2, 2*r_out + 2, r_out]);
    }

    // Dual 25mm elastic band brackets (+/- Y)
    strap_w = STRAP_WIDTH_HEADBAND + 1.0;
    strap_th = 3.0;
    wing_w = 8.0;

    difference() {
        union() {
            translate([-p_len/2, -p_width/2 - wing_w, -4.0]) cube([p_len, wing_w, 4.0]);
            translate([-p_len/2,  p_width/2,          -4.0]) cube([p_len, wing_w, 4.0]);
        }
        translate([-strap_w/2, -p_width/2 - wing_w/2 - strap_th/2, -4.5]) cube([strap_w, strap_th, 5.0]);
        translate([-strap_w/2,  p_width/2 + wing_w/2 - strap_th/2, -4.5]) cube([strap_w, strap_th, 5.0]);
    }
}

// 6. HALLUX (BIG TOE) MOUNT
module mount_hallux() {
    core_cradle_sleeve();

    r_in = HALLUX_INNER_DIAMETER / 2.0;
    th = 2.4;
    r_out = r_in + th;

    // Great toe saddle
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

    // Lateral toe strap loops (+/- Y) for 15mm strap
    loop_w = 7.0;
    slot_l = 15.5;
    slot_th = 2.4;

    difference() {
        union() {
            translate([-slot_l/2 - 3.5, -out_w/2 - loop_w, -4.5]) cube([slot_l + 7, loop_w, 4.5]);
            translate([-slot_l/2 - 3.5,  out_w/2,          -4.5]) cube([slot_l + 7, loop_w, 4.5]);
        }
        translate([-slot_l/2, -out_w/2 - loop_w/2 - slot_th/2, -5.0]) cube([slot_l, slot_th, 5.5]);
        translate([-slot_l/2,  out_w/2 + loop_w/2 - slot_th/2, -5.0]) cube([slot_l, slot_th, 5.5]);
    }
}

// =============================================================================
// Top-Level Assembly Dispatcher
// =============================================================================

module cognilink_cradle(mount=MOUNT_TYPE) {
    color([0.2, 0.65, 0.85]) {
        if (mount == "UNIVERSAL") mount_universal();
        else if (mount == "FINGER")    mount_finger_ring();
        else if (mount == "WRIST")     mount_wrist();
        else if (mount == "EYEGLASS")  mount_eyeglass_clip();
        else if (mount == "HEADBAND")  mount_headband();
        else if (mount == "HALLUX")    mount_hallux();
        else mount_finger_ring();
    }

    // Optional reference mockup of the M5StickC seated inside
    if (SHOW_MOCKUP) {
        translate([0, 0, BASE_THICKNESS])
            m5stickc_mockup();
    }
}

// Simple internal representation of M5StickC for mockup preview
module m5stickc_mockup() {
    color([0.98, 0.45, 0.05, 0.85]) {
        translate([-48.2/2, -25.5/2, 0])
            cube([48.2, 25.5, 13.7]);
    }
    // LCD
    color([0.1, 0.1, 0.12]) {
        translate([-13.0, -8.0, 13.7])
            cube([26.0, 16.0, 0.2]);
    }
    // Button A
    color([0.3, 0.3, 0.3]) {
        translate([15.0, -5.0, 13.7])
            cube([6.0, 10.0, 0.5]);
    }
}

// Render active mount configuration
cognilink_cradle(MOUNT_TYPE);
