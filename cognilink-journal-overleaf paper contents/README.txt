CogniLink journal article: Overleaf package
==========================================

Compiling
  Upload the zip to Overleaf as a new project. Keep the default compiler
  (pdfLaTeX) and main document (main.tex). BibTeX runs automatically.

Your figure files
  Put your six images in the figures/ folder with these exact names. Each
  one replaces its grey placeholder box automatically:
    figures/fig1_wearable_mounting.png      -> Fig. 1 (mounting sites)
    figures/fig2_hardware_architecture.png  -> Fig. 3 (hardware architecture)
    figures/fig3_firmware_state_machine.png -> Fig. 4 (state machine; optional,
                                               a vector diagram is drawn if absent)
    figures/fig4_communicator_ui.png        -> Fig. 6 (communicator screenshots)
    figures/fig5_testbed_setup.png          -> Fig. 8 (latency testbed)
    figures/fig6_benchmarks.png             -> Fig. 9 (benchmark panels a to f)
  If a file is a JPG or PDF instead of PNG, change the file name in main.tex.
  Figs. 2, 5, and 7 are drawn by the paper itself and need no files.

Bengali text
  Bengali cannot be typeset with pdfLaTeX, so it is pre-rendered:
    snippets/bengali.pdf          Bengali words and sentences (one per page)
    figures/bengali_keyboard.pdf  Bengali keyboard figure (Fig. 7)
  To change them, edit snippets/bengali.tex or figures/bengali_keyboard.tex and
  compile that file with XeLaTeX (fonts: Noto Serif Bengali, Noto Sans Bengali).
  The page map for snippets/bengali.pdf is listed near the top of main.tex.

Red notes in the PDF
  [ ... ]        information only the authors can supply
  [CHECK: ... ]  a number or statement that must be confirmed or corrected
  When all notes are resolved, delete the \tbd and \chk definitions near the
  top of main.tex. Any note left behind will then stop compilation.
