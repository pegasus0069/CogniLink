# CogniLink 3D CAD & Wearable Mechanical Cradle Suite

Welcome to the **CogniLink CAD Repository**. This directory contains the mechanical design files, parametric scripts, and additive manufacturing (3D printing) assets for the **CogniLink Wearable Assistive Pointer System**.

The cradle system securely retains an **M5Stack M5StickC** development kit ($48.2 \times 25.5 \times 13.7$ mm, $15.1$ g) and translates residual microscopic motor articulation across **5 anatomical mounting sites** into standard Bluetooth Low Energy (BLE) Human Interface Device (HID) mouse input.

---

## 1. Correlation with the IEEE Journal Paper

All designs in this directory directly correlate with the hardware descriptions, biomechanical analyses, and cost models presented in the CogniLink research article:
- **Section IV-B (*Form Factor and Mounting Sites*)**: Details the primary finger ring configuration and the four alternative anatomical sites (wrist strap, eyeglass temple clip, elastic headband, and hallux toe mount).
- **Section IV-C (*Processing, Sensing, and Power*)**: Specifies module dimensions ($48.2 \times 25.5 \times 13.7$ mm), screen orientation (0.96" TFT LCD), button placements (Button A on front, Button B on side), and USB-C charging access.
- **Table XI / XII (*Bill of Materials*)**: Itemizes the in-house FDM 3D-printed PETG cradle at **US\$0.45 (53 BDT)**, contributing to the total **US\$15.00 (1,770 BDT)** autonomous hardware cost.
- **Figure 1 (*Biomechanical Wearable Mounting Configurations*)**: Illustrates the physical deployment of the module across the five clinical sites.

---

## 2. Directory Structure

```
cad/
├── README.md                          # Mechanical engineering documentation & printing guide
├── stl/                               # Production-ready watertight binary STL files
│   ├── cognilink_universal_cradle.stl     # Universal carrier with dual 15x2.5mm strap loops
│   ├── cognilink_finger_ring_cradle.stl   # Primary proximal phalanx dorsal saddle (R=10.5mm)
│   ├── cognilink_wrist_mount_cradle.stl   # Broad carpal saddle with 20.5mm medical band loops
│   ├── cognilink_eyeglass_temple_clip.stl # Dual-jaw tension clip for 2.5-5.0mm frame arms
│   ├── cognilink_headband_mount_cradle.stl# Cranial curved plate (R=80mm) with 26mm band loops
│   └── cognilink_hallux_toe_mount.stl     # Pedal dorsal saddle with distal articulation relief
├── openscad/                          # Fully parametric OpenSCAD source models
│   ├── cognilink_cradle_system.scad       # Master parametric customizer for all 6 configurations
│   ├── cognilink_finger_ring.scad         # Standalone customizer for finger ring sizing
│   ├── cognilink_eyeglass_clip.scad       # Standalone customizer for spectacle frame clamping
│   └── m5stickc_mockup.scad               # Reference 3D mockup of M5StickC for fit verification
└── scripts/
    └── generate_stls.py               # Procedural binary STL mesh generator (pure NumPy)
```

---

## 3. Specifications of the 3D Models

All models feature a precision snap-fit sleeve engineered with a **$0.30$ mm per side clearance** for standard fused deposition modeling (FDM), a base thickness of **$1.8$ mm**, wall thickness of **$1.8$ mm**, and **$0.50$ mm snap retention lips** along the top long edges.

| File Name | Anatomical Target | Degrees of Freedom Captured | Target Patient Clinical Presentation | Dimensions ($X \times Y \times Z$) | Triangle Count |
| :--- | :--- | :--- | :--- | :---: | :---: |
| **`cognilink_universal_cradle.stl`** | Universal / Multipurpose | Linear / Angular tilt across any flat or contoured limb | Robotic arm mounts, wheelchair brackets, testing rigs | $52.4 \times 45.7 \times 12.8$ mm | 300 |
| **`cognilink_finger_ring_cradle.stl`** | Proximal phalanx (index or middle finger) | Finger flexion/extension ($Y$-axis) & hand pronation/supination ($X$-axis) | Motor neuron disease, ALS, stroke with residual distal finger movement | $52.4 \times 41.7 \times 16.8$ mm | 512 |
| **`cognilink_wrist_mount_cradle.stl`** | Dorsal carpal bones (wrist) | Radial & ulnar deviation, forearm pronation | Hand spasticity, severe finger contractures with intact wrist mobility | $74.4 \times 56.0 \times 17.8$ mm | 544 |
| **`cognilink_eyeglass_temple_clip.stl`** | Spectacle temple arm ($2.5$–$5.0$ mm) | Cervical nodding (pitch) & lateral head tilt (roll) | High cervical spinal cord injury (C3–C5 tetraplegia) with head control | $52.4 \times 42.1 \times 12.8$ mm | 192 |
| **`cognilink_headband_mount_cradle.stl`** | Frontal cranial bone (forehead) | Cervical nodding & head axial rotation | Advanced muscular dystrophy, locked-in syndrome with subtle neck rotation | $62.4 \times 80.0 \times 18.9$ mm | 576 |
| **`cognilink_hallux_toe_mount.stl`** | Dorsum of great toe (hallux) | Pedal dorsiflexion/plantarflexion & foot eversion | Bilateral upper-limb amputation, dysmelia with preserved foot articulation | $52.4 \times 43.7 \times 17.3$ mm | 512 |

---

## 4. Mechanical Design Features

1. **Uninterrupted Port & Button Access**:
   - **USB-C Port**: Cutout on the $-X$ bottom wall ($12.0 \times 7.0$ mm) allows battery charging and firmware flashing without removing the unit from its cradle.
   - **Button B (Reset/Settings)**: Cutout on the $+Y$ lateral wall ($10.0 \times 6.0$ mm) allows triggering the calibration reset countdown.
   - **Display & Button A**: Top face is completely open, giving full visibility to the $0.96$-inch $80 \times 160$ LCD status display and tactile access to the front click button (Button A).
2. **Snap-Fit Retention**:
   - Integrated $45^\circ$ lead-in chamfers with $0.50$ mm overhangs securely clamp the M5StickC casing, preventing vibration-induced rattle during high-velocity gestures while enabling tool-free insertion and extraction.
3. **Ergonomic Biocompatibility**:
   - Concave dorsal surfaces are anatomically curved to distribute contact pressure over digital and carpal skin, preventing pressure ischemia during extended sessions.
   - Lateral wings incorporate smooth radiused strap channels for washable silicone or hook-and-loop elastic fasteners.

---

## 5. Additive Manufacturing & Slicing Guide

To achieve clinical durability, skin biocompatibility, and snap-fit flexural strength, parts should be fabricated according to the following parameters:

### Recommended Slicer Settings (PETG Filament)
- **Material**: **PETG** (Polyethylene Terephthalate Glycol)
  *(PLA may be used for rapid prototyping, but PETG is strongly recommended for clinical deployment due to higher fatigue resistance, layer adhesion, and alcohol sanitization resistance).*
- **Print Temperature**: $235^\circ\text{C}$ to $245^\circ\text{C}$
- **Bed Temperature**: $70^\circ\text{C}$ to $80^\circ\text{C}$ (textured PEI sheet recommended)
- **Layer Height**: **$0.20$ mm** ($0.12$ mm adaptive layers can be enabled for the top snap lips)
- **Perimeters (Walls)**: **4 perimeters** (using a standard $0.40$ mm nozzle). This ensures all cradle walls are $100\%$ solid continuous polymer without hollow voids.
- **Infill**: **$100\%$ Rectilinear** (maximizes clamping rigidity and eliminates internal moisture pockets).
- **Print Orientation**: Orient with the **flat base sitting directly on the build plate**.
- **Supports**: **None required**. All geometries and cutouts are self-supporting when printed flat.
- **Brim**: Optional $3$ mm outer brim if printing on smooth PEI beds without adhesive.

### Estimated Manufacturing Cost & Print Time
- **Mass**: $\approx 5.5$ to $8.2$ grams per cradle.
- **Print Time**: $22$ to $38$ minutes on a modern high-speed 3D printer (e.g., Bambu Lab P1/X1, Prusa MK4/Core, Creality K1).
- **Material Cost**: $\approx \text{US\$0.15}$ to $\text{US\$0.45}$ ($\approx 18$ to $53$ BDT) based on standard 1 kg PETG filament rolls ($\approx \text{US\$18.00}$/kg).

---

## 6. Assembly & Clinical Disinfection Protocol

### Insertion Procedure
1. Verify that the M5StickC module is turned off or in idle state.
2. Align the bottom USB-C connector with the $-X$ cutout of the cradle.
3. Press the front of the module gently downward into the pocket until an audible click indicates that both lateral snap lips have engaged the top edges.
4. Ensure the screen is centered and Button B is accessible through the side aperture.

### Extraction Procedure
1. Grasp the lateral outer walls of the cradle with thumb and forefinger.
2. Flex the sidewalls slightly outward while pressing upward on the bottom floor slot to push the module out.

### Clinical Cleaning & Disinfection
- **Sanitization**: Wipe all surfaces thoroughly with **70% Isopropyl Alcohol (IPA)** or hospital-grade quaternary ammonium antiseptic wipes.
- **Washability**: The 3D-printed PETG cradle and silicone straps can be washed in warm soapy water ($< 60^\circ\text{C}$). Do not autoclave above $75^\circ\text{C}$ (PETG glass transition temperature is $\approx 80^\circ\text{C}$).

---

## 7. Parametric Customization via OpenSCAD

For non-standard anatomical dimensions (e.g., pediatric finger sizes or thick spectacle frames), customize the models using the OpenSCAD scripts in `openscad/`:

1. Open `cad/openscad/cognilink_cradle_system.scad` in [OpenSCAD](https://openscad.org/).
2. In the **Customizer** panel (Window $\rightarrow$ Customizer), select:
   - `MOUNT_TYPE`: `"FINGER"`, `"WRIST"`, `"EYEGLASS"`, `"HEADBAND"`, `"HALLUX"`, or `"UNIVERSAL"`.
   - `FINGER_INNER_DIAMETER`: Adjust from $16.0$ mm (pediatric) to $24.0$ mm (large adult).
   - `EYEGLASS_TEMPLE_THICKNESS`: Adjust from $2.0$ mm to $6.0$ mm.
   - `TOLERANCE`: Adjust snap-fit offset for tighter or looser fit ($0.20$ to $0.40$ mm).
3. Press **F5** (Preview) or **F6** (Render), then **File $\rightarrow$ Export as STL**.

### Procedural STL Re-generation via Python
To programmatically regenerate all binary STL models from source code:
```bash
python cad/scripts/generate_stls.py
```
This runs the standalone procedural synthesis engine and verifies bounding dimensions, vertex winding, and manifold triangle counts.
