CogniLink Journal Article: Overleaf & Manuscript Package
=========================================================

1. Manuscript Overview
----------------------
Title: CogniLink: A $15 Autonomous Wearable Pointer and Bilingual 
       Bengali-English Augmentative Communicator for Profound Motor Impairment
Format: IEEE Transactions (IEEEtran, journal mode, two columns, 18 pages)
Engine: pdfLaTeX with BibTeX (Overleaf default). Compiles with 0 errors.

2. Compiling on Overleaf
------------------------
- To upload to Overleaf:
  Create a new Overleaf project by uploading the contents of this folder 
  (or a zip of this directory).
- Settings:
  - Compiler: pdfLaTeX (default)
  - TeX Live version: 2024 or latest
  - Main document: main.tex
  - BibTeX runs automatically on references.bib.

3. Figures and Vector Diagrams
------------------------------
All figure image assets and vector drawings are pre-configured and included
in the figures/ directory:

  Image / Vector File                       Figure Number and Content
  ----------------------------------------  -------------------------------------------------------------
  figures/fig1_wearable_mounting.png     -> Fig. 1: Biomechanical wearable mounting configurations
                                                    (finger ring, wrist strap, eyeglass clip,
                                                    headband, and hallux toe mount).
  [Native TikZ vector code in main.tex]  -> Fig. 2: System architecture and inter-device communication
                                                    model (Core 1 kinematic pointing, Core 0 web stack,
                                                    BLE 4.2 HID mouse link, and Wi-Fi web link).
  figures/fig2_hardware_architecture.png -> Fig. 3: Hardware architecture and electrical block diagram
                                                    (ESP32-PICO-D4, MPU-6886 IMU, AXP192 PMIC,
                                                    ST7735S LCD, Buttons A/B, battery, and USB-C).
  figures/fig3_firmware_state_machine.png-> Fig. 4: Firmware state machine (States S0 to S6) with
                                                    measured power telemetry and transition guards.
  [Native PGFPlots code in main.tex]     -> Fig. 5: Non-linear velocity control law with deadzone
                                                    threshold subtraction and saturation clipping.
  figures/fig4_communicator_ui.png       -> Fig. 6: Self-hosted bilingual AAC communicator UI with
                                                    animated dwell selection and medical emergency tray.
  figures/bengali_keyboard.pdf           -> Fig. 7: Bengali phonological keyboard layout organized by
                                                    traditional place of articulation with hasanta
                                                    conjunct ligature synthesis.
  figures/fig5_testbed_setup.png         -> Fig. 8: 240 fps optical testbed setup for end-to-end
  (or figures/fig_testbed_setup.png)                motion-to-photon latency characterization.
  figures/fig6_benchmarks.png            -> Fig. 9: Complete empirical bench characterization (panels
  (or figures/fig5_benchmarks.png)                  a-f: latency, drift, dwell accuracy, speech onset,
                                                    HID report intervals, and battery discharge).

Individual high-resolution benchmark panels are also provided in figures/:
  - fig5a_end_to_end_latency.png        (Motion-to-photon latency on 60 Hz TV)
  - fig5b_stationary_drift.png          (Resting drift with deadzone on vs. off)
  - fig5c_dwell_timing_accuracy.png     (Dwell timing across 4 nominal intervals)
  - fig5d_speech_onset_latency.png      (Bilingual audio speech onset latency)
  - fig5e_hid_report_intervals.png      (NimBLE HID mouse reporting intervals)
  - fig5f_battery_discharge.png         (AXP192 battery discharge profiles)

4. Bengali Typesetting & Snippets
---------------------------------
Because standard pdfLaTeX does not support complex Brahmic script rendering
natively, all Bengali words, conjunct examples, and keyboards are pre-rendered
using XeLaTeX into high-resolution vector PDF assets:
  - snippets/bengali.pdf         : Bengali words, phrases, and conjuncts (1 per page)
  - figures/bengali_keyboard.pdf : Full-page Bengali keyboard layout (Fig. 7)

To modify any Bengali text, edit snippets/bengali.tex or figures/bengali_keyboard.tex
and recompile with XeLaTeX (requires Noto Serif Bengali and Noto Sans Bengali fonts).

snippets/bengali.pdf Page Mapping:
  Pages 1 to 8   : Emergency phrase button labels
  Pages 9 to 16  : Spoken Bengali emergency phrases (matches Table V)
  Page 17        : Conjunct example (kta = ka + hasanta + ta)
  Page 18        : The word "hasanta" in Bengali script
  Page 19        : Representative yuktakshara conjuncts (Table VI)
  Page 20        : Standalone virama / hasanta sign
  Pages 21 to 22 : Keyboard layout sub-headers and shift states

5. Current Manuscript Status & Resolved Checks
----------------------------------------------
- All author confirmation placeholders ([CHECK: ...]) and notes have been
  completely verified, corrected, and cleared:
  - Round-trip ping is measured at 30 to 50 ms.
  - 2.4 GHz Wi-Fi bandwidth is specified at up to 72.2 Mb/s (802.11b/g/n, HT20, 1x1 SISO).
  - Microcontroller terminology updated to "microcontroller with an IMU".
  - Component sourcing reflects local Dhaka component distributors and online retail ($15.00 BOM).
  - Fig. 2 architecture badge alignment is centered and non-overlapping.
  - Future work explicitly details upcoming trial runs in hospital and home settings.
  - Acknowledgments officially recognize Fab Lab IUB and IUB360 for providing testing and fabrication facilities.
  - Conclusion is written to Q1 journal standards with full bilingual keyboard coverage.

6. Open-Source Hardware, CAD, and Data Availability
---------------------------------------------------
All accompanying project materials correlate with the repository root:
  - cad/stl/      : Production-ready 3D-printable PETG mounting cradles for all 5 sites
  - cad/openscad/ : Parametric OpenSCAD customizers for personalized patient sizing
  - cad/README.md : Mechanical printing guide and clinical sanitization protocols
  - datasets/     : Raw 10,000-trial benchmark CSV datasets
  - m5stickc/     : Arduino/ESP32 dual-core firmware and embedded bilingual communicator
