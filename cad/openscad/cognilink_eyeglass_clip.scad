// =============================================================================
// CogniLink Assistive Technology - Eyeglass Temple Clip Cradle (Standalone)
// =============================================================================
// Dedicated parametric OpenSCAD model for the spectacle temple arm clip.
// Designed for users with high cervical spinal cord injury (C3-C5 tetraplegia)
// who retain voluntary head movement.
//
// Aligns sensor pitch with cervical nodding and roll with lateral head tilt.
// =============================================================================

/* [Eyeglass Clip Parameters] */
// Thickness of the spectacle frame temple arm (mm) - standard frames = 2.5 to 5.0 mm
TEMPLE_THICKNESS = 3.2;

// Internal clearance for M5StickC snap fit (mm)
TOLERANCE = 0.30;

// Gripping jaw height (mm)
CLIP_HEIGHT = 9.0;

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

module eyeglass_temple_cradle() {
    difference() {
        hull() {
            r_c = 2.0;
            translate([-out_l/2 + r_c, -out_w/2 + r_c, 0]) cylinder(r=r_c, h=tot_h);
            translate([ out_l/2 - r_c, -out_w/2 + r_c, 0]) cylinder(r=r_c, h=tot_h);
            translate([-out_l/2 + r_c,  out_w/2 - r_c, 0]) cylinder(r=r_c, h=tot_h);
            translate([ out_l/2 - r_c,  out_w/2 - r_c, 0]) cylinder(r=r_c, h=tot_h);
        }

        translate([-cav_l/2, -cav_w/2, BASE_THICKNESS])
            cube([cav_l, cav_w, POCKET_DEPTH + 1.0]);

        translate([-out_l/2 - 0.5, -6.0, BASE_THICKNESS])
            cube([WALL_THICKNESS + 1.0, 12.0, 7.0]);

        translate([0.0, cav_w/2 - 0.5, BASE_THICKNESS])
            cube([10.0, WALL_THICKNESS + 1.0, 6.0]);

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

    // Eyeglass temple clip
    clip_len = 32.0;
    clip_gap = TEMPLE_THICKNESS;
    jaw_th = 2.0;
    clip_depth = CLIP_HEIGHT;
    bridge_w = 4.0;

    translate([-clip_len/2, -out_w/2 - bridge_w, 2.0])
        cube([clip_len, bridge_w, clip_depth]);

    y_inner = -out_w/2 - bridge_w;
    translate([-clip_len/2, y_inner - jaw_th, 0])
        cube([clip_len, jaw_th, clip_depth + 2.0]);
    translate([-clip_len/2, y_inner - jaw_th - clip_gap - jaw_th, clip_depth])
        cube([clip_len, clip_gap + 2*jaw_th, 2.0]);
    translate([-clip_len/2, y_inner - 2*jaw_th - clip_gap, 0])
        cube([clip_len, jaw_th, clip_depth + 2.0]);
    translate([-clip_len/2, y_inner - 2*jaw_th - clip_gap - 1.2, 0])
        cube([clip_len, 1.2, 1.8]);
}

// Render model
color([0.85, 0.35, 0.55])
    eyeglass_temple_cradle();
