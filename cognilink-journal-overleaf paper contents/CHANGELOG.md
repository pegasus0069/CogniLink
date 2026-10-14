# CogniLink journal draft: change report (14 Oct 2026)

Compares three things: the previous 6-page conference draft, your file
PAPER_SPECIFICATIONS_AND_BENCHMARKS.md (the "spec"), and the journal draft.

## 1. Pictures in the files you gave me

| File | What it contains |
|---|---|
| CogniLink_Research_Information_Pack.docx | No figures. Its only embedded image is a blank 1 x 1 pixel used 31 times as a link icon in the source list. The 1.9 MB size comes from embedded fonts. |
| Outputs_of_agents_regarding_lit_review.docx | No figures. The same blank link icon, used 68 times. |
| PAPER_SPECIFICATIONS_AND_BENCHMARKS.md | Links to six images (`figures/fig1_wearable_mounting.png` to `figures/fig6_benchmarks.png`). The image files were not uploaded, so I could not see them. |

Because of this, every caption for your six figures now says only what the spec
itself says the figure shows. Nothing is assumed about the pictures. The spec
never describes panel (b) of fig6, so that caption has a CHECK note.

## 2. Previous conference draft compared with the journal draft

| Part | Previous draft (conference) | Journal draft |
|---|---|---|
| Format | IEEE conference, 6 pages | IEEE journal (IEEEtran journal mode), 16 pages |
| Title | Low-Cost Finger-Worn Pointer and Bilingual Bengali-English AAC Prototype | The spec's title, with "Ultra-" removed |
| Abstract | Cost US$30 and results left blank | Written last; US$15 and measured results |
| Introduction | Need, statistics, 3 contributions | Same evidence kept; Bengali speaker figure, gap paragraph, 4 contributions, outline added |
| Related work | AAC, motion pointing, dwell, Table I | All kept; added word prediction (Koester and Levine) and Bengali text entry (Sarcar et al., Arif and Fardeen); Table I cost now US$15 |
| Design goals | G1 to G6 | Kept; G1 lists the five mounting sites, G6 adds drift |
| System design | One section with many blanks | Split into Hardware, Firmware, and Communicator, filled from the spec |
| IMU | "SH200Q or MPU6886" (blank) | MPU-6886, with datasheet values |
| Battery | 95 mAh | 80 mAh as in the spec (CHECK: brief and M5Stack say 95 mAh after March 2020) |
| Control law | Simple deadzone without threshold subtraction | The spec's law (threshold subtraction, rounding, clipping), plus onset, speed, and saturation analysis and a plot |
| Calibration, report rate, gain | Blanks | 1.0 s + 150 samples at 10 ms; 50 Hz; theta 1.20 deg/s; K 0.60 |
| State machine | 7 informal states | Spec states S0 to S6 with currents and transition times (diagram and table) |
| Dwell | Fixed 5 s, range blank | 0.5, 1.0, 2.0, 5.0 s; ring geometry equation |
| Emergency phrases | Number blank | 8 phrases in English and Bengali (Bengali typeset correctly) |
| Keyboards | Layout blank | QWERTY with symbol tab; varga-ordered Bengali tabs (new figure) |
| Speech | Provider blank | Google Translate endpoint plus Web Speech API fallback; privacy discussion |
| Cost table | Blanks | Itemized US$15.00 (1,770 BDT) |
| Evaluation | Planned 50 trials with 240 fps video, 20 dwell trials | Spec methods and 10,000-trial results; host table; latency, drift, power, compatibility tables |
| Discussion | Positioning, dwell, Bengali, limitations, future work | All kept and extended: latency in context, deadzone design, large bedside displays, privacy and safety |
| References | 34 cited | 55 cited (21 added, none dropped), all checked against publisher or manufacturer pages |

## 3. Spec content added in this revision

1. Title and index terms from the spec (Bengali orthography, microcontroller firmware, vertical synchronization).
2. Spinal cord injury at the C3 to C5 levels.
3. Mounting: dominant index or middle finger; PETG cradle printed in-house by FDM; adjustable hook-and-loop strap; wrist (radial and ulnar deviation); eyeglass temple (pitch and roll); headband (neck rotation, muscular dystrophy); hallux (bilateral upper-limb amputation or dysmelia).
4. ESP32-PICO-D4: 448 KB ROM, Wi-Fi up to 150 Mb/s, core assignment.
5. MPU-6886: 3 x 3 x 0.75 mm package, I2C address 0x68.
6. Battery energy 0.296 Wh; charge estimated from the AXP192 voltage reading.
7. BLE name "CogniLink Finger" and WiFiManager captive portal (from the earlier brief); hardware coexistence arbitration.
8. Full state table: subsystems, guards, next states, and transition times for S0 to S6.
9. Y-axis rate used for orientation telemetry, not for pointing.
10. Single-page app stored as `const char* INDEX_HTML`; light and dark themes; custom assistive cursor.
11. Four-display key-size table (tablet, laptop, desktop, television), including the space bar; 3.7 to 4.2 cm letter keys and 13.9 cm phrase keys on the television at 1.5 to 2.5 m.
12. Keyboard tab labels, 39 consonant letters and signs, example conjuncts, shaping engines.
13. Emergency table with the exact button labels, a Priority column, and the spec's clinical intent for each phrase.
14. Character-by-character and full-sentence speech; HTTPS and HTML5 Audio; 3 s auto-clear (CHECK).
15. Host table with full processor, memory, operating system, and browser details.
16. Television details (HQLED, quantum-dot VA panel, HDMI 2.1, Game Mode settings).
17. Latency testbed details (push-pull GPIO within 1 us, 4-channel 50 MHz scope, shroud, dark-to-white change, single-shot trigger, timebase cursors, trained operator instead of a shaker).
18. Latency sub-stages on the host (0.6 to 1.2, 0.4 to 0.8, 0.8 to 1.5, 0.7 to 2.0 ms) and the VA panel transition (6.5 to 8.5 ms); I2C read time before t0.
19. HID interval range as rates (60.6 to 39.3 Hz); all four dwell relative errors and the 0.17% average.
20. Power table with connection states and the intended use of each scenario; 6.5-digit multimeter.
21. Linux pairing through BlueZ; BOM source column; studio condenser microphone.
22. New discussion subsection on large displays at the bedside.

## 4. Spec content corrected or left out, and why

| Spec statement | What the draft does | Reason |
|---|---|---|
| "Ultra-low-cost", "clinical-grade", "prove", "complete suppression", "sub-millisecond", "microscopic", "100% locked" | Removed | Not supported by the data or overstated |
| Eye trackers US$7,200 to 10,200; head mice US$550 to 895; 97.3 to 99.8% cheaper | Replaced with verified prices (US$599, 999, 1,249) and 97.5 to 98.8% | Prices could not be verified |
| Bengali "sixth, 270 million native speakers" | About 273 million total speakers, seventh | Britannica (Ethnologue data) |
| Commercial AAC lacks Bengali keyboards | Narrower claim | Cboard supports Bengali |
| Tobii Dynavox I-Series, PRC-Saltillo Accent, eye strain and daylight problems | Not included | No verified source in the reference list |
| Locked-in syndrome as a target group; headband senses forehead muscle | Neck rotation only | A gyroscope senses rotation, not muscle activity; classic locked-in syndrome leaves no head movement |
| "IPS" display | TFT | M5Stack documentation |
| 600 DMIPS | Left out | Not in the ESP32-PICO series datasheet v1.4 |
| DLPF 42 Hz; 4.8 ms delay from "DS-000216 Table 16" | 41 Hz; no delay value | MPU-6886 datasheet DS-000193: 41 Hz gyroscope, 42 Hz is the temperature sensor, no delay column |
| Noise density 0.005 deg/s/rtHz | 0.004 | Datasheet typical value |
| I2C burst read 63 cycles (157.5 us) | 81 cycles (about 0.2 ms) | The register address must be written before the six data bytes are read |
| BLE stage 15 to 22.5 ms (typical 18.8); IMU stage inside the measured latency; 33.33 ms = 2 frames, 54.17 ms = 3 frames | Corrected latency model and a CHECK | The wait for a connection event averages half the interval; sensing happens before t0; 3 frames = 50.0 ms |
| Rigol DS1054Z "10 MS/s, 50 ohm termination" | Left out | Published specification is 50 MHz and 1 GSa/s; 50 ohm input not confirmed |
| performance.now() "< 5 us precision" | Left out | Chrome gives 100 us unless the page is cross-origin isolated, which needs a secure (HTTPS) page |
| Chromium uses "Pango/FreeType" on Linux | Left out | Chromium shapes text with HarfBuzz |
| Biocompatible, medical-grade, hypoallergenic parts | Left out | No certification given |
| Game Mode scaler delay of 1.5 ms or less | Left out | Not measured |
| "Sub-60 ms onset ensures conversational responsiveness"; "50 to 100 ms perceptual threshold" | Replaced with MacKenzie and Ware (1993) | No source given |
| Drift summary 25.14 +/- 3.64 px, t = 15.45, p = 7.82e-5 | 25.44 +/- 4.16 px, t(4) = 13.69, p = 1.7e-4 | Recomputed from the spec's own per-run values |
| "Measured" runtimes 39.5 to 115.7 min and 38.1 h | Shown as estimates with eta = 0.95; undivided values in the note | They equal 80 mAh divided by current exactly |
| 500 mAh power bank gives over 8.5 h | Removed | Arithmetic gives about 4 h |
| Dwell timing "governed solely by VSync quantization" | Left out; CHECK | Negative errors contradict it |
| Twelve vowels | Eleven | The spec's own list has eleven |
| Drift caused by thermal noise and random walk | CHECK | With per-report rounding, rates below 0.83 deg/s give no counts |

## 5. Still needed from you

See the red notes in the PDF and `open-items.md`. Most important: upload the six
figure files, confirm the battery capacity, and resolve the data CHECK notes
(latency grid, battery runtimes, dwell extremes, HID intervals, drift mechanism,
axis sign) before submission.
