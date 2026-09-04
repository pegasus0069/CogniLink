#ifndef INDEX_H
#define INDEX_H

const char* INDEX_HTML = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="referrer" content="no-referrer">
    
    <title>CogniLink Communicator</title>
    <style>
        :root {
            /* SOOTHING LIGHT THEME */
            --bg-color: #EFE9E1; 
            --surface-bg: #F8F5F1; 
            --primary: #D4A3B3; 
            --primary-hover: #E8D3DA;
            --text-main: #4A4043;
            --text-light: #8A7A7F;
            --danger: #E57373;
            --danger-bg: #FCE4E4;
            --success: #81C784;
            --success-bg: #E3F1E4;
            --warning: #FFB74D;
            --warning-bg: #FDF0DE;
            --key-bg: #F0EAE3; 
            --key-border: #DBC7CC;
            --shadow: 0 4px 15px rgba(212, 163, 179, 0.2);
        }

        body.dark-mode {
            /* DARK THEME */
            --bg-color: #121212;
            --surface-bg: #1E1E1E;
            --primary: #D4A3B3; 
            --primary-hover: #3D2C31;
            --text-main: #E0E0E0;
            --text-light: #A0A0A0;
            --danger: #EF5350;
            --danger-bg: #401B1C;
            --success: #66BB6A;
            --success-bg: #1B3820;
            --warning: #FFA726;
            --warning-bg: #4A3311;
            --key-bg: #2C2C2C;
            --key-border: #444444;
            --shadow: 0 4px 15px rgba(0, 0, 0, 0.5);
        }

        * { cursor: url('data:image/svg+xml;utf8,<svg width="36" height="36" viewBox="0 0 36 36" xmlns="http://www.w3.org/2000/svg"><circle cx="18" cy="18" r="12" fill="rgba(212,163,179,0.3)" stroke="%23D4A3B3" stroke-width="2.5"/><circle cx="18" cy="18" r="4" fill="%23D4A3B3"/></svg>') 18 18, auto !important; }
        button, .tab-btn { cursor: url('data:image/svg+xml;utf8,<svg width="40" height="40" viewBox="0 0 40 40" xmlns="http://www.w3.org/2000/svg"><circle cx="20" cy="20" r="16" fill="rgba(129,199,132,0.3)" stroke="%2381C784" stroke-width="3"/><circle cx="20" cy="20" r="5" fill="%2381C784"/></svg>') 20 20, pointer !important; }

        body { 
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; 
            background-color: var(--bg-color); color: var(--text-main); 
            margin: 0; padding: 15px; min-height: 100vh;
            display: flex; flex-direction: column; align-items: center;
            box-sizing: border-box; overflow-y: auto; transition: all 0.3s ease;
        }

        .status-bar {
            width: 100%; max-width: 1200px; display: flex; justify-content: space-between; align-items: center;
            padding: 10px 20px; background: var(--surface-bg); border-radius: 12px;
            box-shadow: var(--shadow); margin-bottom: 15px; box-sizing: border-box;
            font-size: 1.1rem; color: var(--text-light); border: 1px solid var(--key-border); position: relative;
        }
        
        .logo-container { 
            display: flex; align-items: center; gap: 10px; font-weight: 800; font-size: 1.4rem; 
            color: var(--primary); letter-spacing: 1px;
            font-family: 'Consolas', 'Courier New', monospace;
        }

        .status-indicator { display: flex; align-items: center; gap: 10px; font-weight: 600; }
        .dot { width: 12px; height: 12px; border-radius: 50%; background: var(--danger); }
        .connected .dot { background: var(--success); box-shadow: 0 0 8px var(--success); }
        
        .settings-icon { font-size: 1.6rem; cursor: pointer; padding: 5px; border-radius: 8px; transition: 0.2s;}
        .settings-icon:hover { background: var(--primary-hover); }

        .settings-menu {
            position: absolute; top: 60px; right: 0px; background: var(--surface-bg);
            border: 1px solid var(--key-border); border-radius: 12px; padding: 15px;
            box-shadow: var(--shadow); display: none; flex-direction: column; gap: 15px; z-index: 100;
        }
        .settings-menu.open { display: flex; }
        .setting-item { display: flex; justify-content: space-between; align-items: center; gap: 30px; font-weight: 600; font-size: 1.1rem; color: var(--text-main);}
        .toggle-group { display: flex; gap: 5px; background: var(--key-bg); border-radius: 8px; padding: 3px; border: 1px solid var(--key-border);}
        .toggle-btn { background: transparent; border: none; padding: 8px 12px; border-radius: 6px; font-weight: bold; color: var(--text-light); font-family: inherit;}
        .toggle-btn.active { background: var(--primary); color: white; box-shadow: var(--shadow);}
        .toggle-btn:disabled { opacity: 0.4; cursor: not-allowed !important; }
        
        #os-badge { font-size: 0.85rem; font-weight: bold; background: var(--primary-hover); color: var(--primary); padding: 4px 8px; border-radius: 6px; text-align: center; font-family: 'Consolas', monospace;}

        .output-container {
            width: 100%; max-width: 1200px; background: var(--surface-bg); border-radius: 15px;
            padding: 20px; margin-bottom: 15px; box-shadow: var(--shadow);
            border: 1px solid var(--key-border); box-sizing: border-box; display: flex; flex-direction: column; gap: 15px;
        }

        #text-output { font-size: 3rem; min-height: 70px; border-bottom: 3px solid var(--primary-hover); padding-bottom: 10px; word-wrap: break-word; color: var(--text-main); font-weight: 500;}
        .action-row { display: flex; gap: 15px; justify-content: space-between; }
        .action-group { display: flex; gap: 15px; }
        
        .tabs { width: 100%; max-width: 1200px; display: flex; gap: 10px; margin-bottom: 10px; }
        .tab-btn { flex: 1; padding: 12px; font-size: 1.4rem; background: var(--surface-bg); border-radius: 10px; color: var(--text-main); border: 1px solid var(--key-border); box-shadow: var(--shadow); font-weight: 600; transition: all 0.2s; font-family: inherit;}
        .tab-btn.active { background: var(--primary); color: white; border-color: var(--primary); }

        .keyboard { width: 100%; max-width: 1200px; display: flex; flex-direction: column; gap: 10px; margin-bottom: 20px;}
        .key-row { display: flex; justify-content: center; flex-wrap: wrap; gap: 10px; }

        button { transition: all 0.15s ease; user-select: none; font-family: inherit; }
        .key-char { background: var(--key-bg); color: var(--text-main); font-size: 2rem; padding: 12px 20px; border-radius: 10px; min-width: 65px; border: 1px solid var(--key-border); font-weight: 500;}
        .key-char:hover, .tab-btn:hover:not(.active) { background: var(--primary-hover); transform: translateY(-2px); border-color: var(--primary); color: var(--primary); }
        .key-char:active { background: var(--primary); color: white; transform: translateY(1px); }

        .key-space { flex-grow: 1; max-width: 800px; font-size: 1.6rem; padding: 12px; background: var(--surface-bg); border-radius: 10px; border: 1px solid var(--key-border); font-weight: 600; color: var(--text-main);}
        .key-space:hover { background: var(--primary-hover); color: var(--primary); border-color: var(--primary); }
        
        .key-action { background: var(--surface-bg); color: var(--text-main); font-size: 1.4rem; padding: 12px 25px; border-radius: 10px; font-weight: 600; border: 1px solid var(--key-border);}
        .key-speak { background: var(--success-bg); color: var(--success); font-size: 1.5rem; padding: 12px 35px; border-radius: 10px; font-weight: bold; border: 1px solid var(--success);}
        .key-clear { background: var(--danger-bg); color: var(--danger); font-size: 1.4rem; padding: 12px 25px; border-radius: 10px; font-weight: bold; border: 1px solid var(--danger);}
        .key-lang { background: var(--warning-bg); color: var(--warning); font-size: 1.5rem; padding: 12px 25px; border-radius: 10px; font-weight: bold; border: 1px solid var(--warning);}

        .key-speak:hover { background: var(--success); color: white; }
        .key-clear:hover { background: var(--danger); color: white; }
        .key-lang:hover { background: var(--warning); color: white; }

        .tray-title { width: 100%; max-width: 1200px; text-align: left; font-size: 1.4rem; font-weight: 700; color: var(--danger); margin-bottom: 10px; border-bottom: 2px solid var(--danger-bg); padding-bottom: 5px;}
        .medical-tray { width: 100%; max-width: 1200px; display: grid; grid-template-columns: repeat(4, 1fr); gap: 10px; padding-bottom: 20px;}
        
        .phrase-btn { 
            background: var(--danger-bg); color: var(--danger); font-size: 1.3rem; padding: 15px; border-radius: 10px; border: 2px solid var(--danger); text-align: center; font-weight: 600; box-shadow: var(--shadow); 
            position: relative; overflow: hidden;
        }
        .phrase-btn:hover { background: var(--danger); color: white; border-color: var(--danger); transform: translateY(-2px); }
        
        .dwell-progress {
            position: absolute; bottom: 0; left: 0; height: 5px; background: white; width: 0%;
            transition: width 0.1s linear;
        }

        ::-webkit-scrollbar { display: none; }
    </style>
</head>
<body>

    <div class="status-bar" id="status-bar">
        <div class="logo-container">
            <svg width="28" height="28" viewBox="0 0 24 24" fill="none" stroke="var(--primary)" stroke-width="2.5" stroke-linecap="round" stroke-linejoin="round">
                <circle cx="18" cy="5" r="3"></circle><circle cx="6" cy="12" r="3"></circle><circle cx="18" cy="19" r="3"></circle>
                <line x1="8.59" y1="13.51" x2="15.42" y2="17.49"></line><line x1="15.41" y1="6.51" x2="8.59" y2="10.49"></line>
            </svg>
            CogniLink
        </div>
        <div class="status-indicator">
            <div class="dot"></div><span id="ws-status">Disconnected</span>
        </div>
        <div class="status-indicator">
            🔋 <span id="bat">--%</span>
            <div class="settings-icon" onclick="toggleSettings()">⚙️</div>
        </div>

        <div class="settings-menu" id="settings-menu">
            <div id="os-badge">System: Scanning...</div>
            <div class="setting-item">
                Theme
                <div class="toggle-group">
                    <button class="toggle-btn active" id="btn-light" onclick="setTheme('light')">Light</button>
                    <button class="toggle-btn" id="btn-dark" onclick="setTheme('dark')">Dark</button>
                </div>
            </div>
            <div class="setting-item">
                Voice Gender
                <div class="toggle-group">
                    <button class="toggle-btn active" id="btn-female" onclick="setGender('female')">Female</button>
                    <button class="toggle-btn" id="btn-male" onclick="setGender('male')">Male</button>
                </div>
            </div>
            <div class="setting-item">
                TTS Engine
                <div class="toggle-group">
                    <button class="toggle-btn active" id="btn-cloud" onclick="setEngine('cloud')">Cloud</button>
                    <button class="toggle-btn" id="btn-offline" onclick="setEngine('offline')">System</button>
                </div>
            </div>
        </div>
    </div>

    <div class="output-container">
        <div id="text-output"></div>
        <div class="action-row">
            <!-- RESTORED id="lang-btn" HERE -->
            <button class="key-lang" id="lang-btn" onclick="toggleLanguage()">🌐 Switch to বাংলা</button>
            <div class="action-group">
                <button class="key-clear" onclick="clearText()">❌ Clear</button>
                <button class="key-action" onclick="backspace()">⌫ Del</button>
                <button class="key-speak" onclick="speakFullText()">🔊 Speak</button>
            </div>
        </div>
    </div>

    <div class="tabs" id="tabs-container"></div>
    <div class="keyboard" id="keyboard"></div>
    
    <div class="tray-title">🏥 Quick Medical Needs (Hover 5s to trigger)</div>
    <div class="medical-tray" id="medical-tray"></div>

    <script>
        let currentLang = 'en'; 
        let currentTab = 'alpha'; 
        let sentence = "";
        let clearTimer = null; 
        
        let prefTheme = 'light';
        let prefGender = 'female';
        let prefEngine = 'cloud'; 

        const display = document.getElementById('text-output');
        const synth = window.speechSynthesis;
        let onlineAudio = new Audio(); 

        function playClickSound() {
            try {
                let audioCtx = new (window.AudioContext || window.webkitAudioContext)();
                let osc = audioCtx.createOscillator();
                let gain = audioCtx.createGain();
                osc.type = 'sine';
                osc.frequency.setValueAtTime(600, audioCtx.currentTime);
                osc.frequency.exponentialRampToValueAtTime(200, audioCtx.currentTime + 0.05);
                gain.gain.setValueAtTime(0.15, audioCtx.currentTime);
                gain.gain.linearRampToValueAtTime(0.01, audioCtx.currentTime + 0.05);
                osc.connect(gain);
                gain.connect(audioCtx.destination);
                osc.start();
                osc.stop(audioCtx.currentTime + 0.05);
            } catch(e) {}
        }

        function detectOS() {
            const ua = navigator.userAgent;
            if (/android/i.test(ua)) return 'Android';
            if (/ipad|iphone|ipod/i.test(ua)) return 'iOS';
            if (/mac/i.test(ua)) return 'macOS';
            if (/win/i.test(ua)) return 'Windows';
            if (/linux/i.test(ua)) return 'Linux';
            return 'Unknown OS';
        }

        function getVoicesSafe() {
            try {
                return synth ? synth.getVoices() || [] : [];
            } catch(e) {
                return [];
            }
        }

        function getVoicesForLang(langCode) {
            let voices = getVoicesSafe();
            return voices.filter(v => {
                let l = (v.lang || '').toLowerCase();
                let n = (v.name || '').toLowerCase();
                if (langCode === 'bn') return l.includes('bn') || n.includes('bangla') || n.includes('bengali');
                else return l.startsWith('en');
            });
        }

        function hasVoiceGender(langCode, gender) {
            let list = getVoicesForLang(langCode);
            if (gender === 'male') {
                return list.some(v => {
                    let n = (v.name || '').toLowerCase();
                    return n.includes('male') || n.includes('david') || n.includes('george') || n.includes('guy') || n.includes('boy');
                });
            } else {
                return list.some(v => {
                    let n = (v.name || '').toLowerCase();
                    return n.includes('female') || n.includes('zira') || n.includes('samantha') || n.includes('girl') || !n.includes('male');
                });
            }
        }

        function getOfflineVoice(langCode, gender) {
            let list = getVoicesForLang(langCode);
            if (list.length === 0) return null;
            let match = null;
            if (gender === 'male') {
                match = list.find(v => {
                    let n = (v.name || '').toLowerCase();
                    return n.includes('male') || n.includes('david') || n.includes('george') || n.includes('guy');
                });
            } else {
                match = list.find(v => {
                    let n = (v.name || '').toLowerCase();
                    return n.includes('female') || n.includes('zira') || n.includes('samantha') || n.includes('girl');
                });
            }
            return match || list[0]; 
        }

        function updateMenuState() {
            const badge = document.getElementById('os-badge');
            if(badge) badge.innerText = "System: " + detectOS();

            let isOnline = navigator.onLine;
            let hasAnyOffline = getVoicesForLang(currentLang).length > 0;
            let hasMaleOffline = hasVoiceGender(currentLang, 'male');
            let hasFemaleOffline = hasVoiceGender(currentLang, 'female');

            const btnCloud = document.getElementById('btn-cloud');
            const btnOffline = document.getElementById('btn-offline');
            const btnMale = document.getElementById('btn-male');
            const btnFemale = document.getElementById('btn-female');
            if(!btnCloud) return;

            if (!isOnline) {
                btnCloud.disabled = true;
                if (prefEngine === 'cloud') prefEngine = 'offline';
            } else {
                btnCloud.disabled = false;
            }

            if (detectOS() === 'Android' && currentLang === 'bn') {
                prefEngine = 'offline';
                btnCloud.disabled = true;
            }

            if (!hasAnyOffline && !(detectOS() === 'Android' && currentLang === 'bn')) {
                btnOffline.disabled = true;
                if (prefEngine === 'offline' && isOnline) {
                    prefEngine = 'cloud';
                }
            } else if (!(detectOS() === 'Android' && currentLang === 'bn')) {
                btnOffline.disabled = false;
            }

            if (prefEngine === 'cloud') {
                btnMale.disabled = true;
                if (prefGender === 'male') prefGender = 'female';
                btnFemale.disabled = false;
            } else if (prefEngine === 'offline') {
                btnMale.disabled = !hasMaleOffline;
                btnFemale.disabled = !hasFemaleOffline;
            }
        }

        window.addEventListener('online', updateMenuState);
        window.addEventListener('offline', updateMenuState);

        function toggleSettings() {
            updateMenuState();
            document.getElementById('settings-menu').classList.toggle('open');
        }

        function setTheme(theme) {
            playClickSound();
            prefTheme = theme;
            document.getElementById('btn-light').classList.remove('active');
            document.getElementById('btn-dark').classList.remove('active');
            document.getElementById(`btn-${theme}`).classList.add('active');
            if (theme === 'dark') document.body.classList.add('dark-mode');
            else document.body.classList.remove('dark-mode');
        }

        function setGender(gender) {
            playClickSound();
            prefGender = gender;
            document.getElementById('btn-female').classList.remove('active');
            document.getElementById('btn-male').classList.remove('active');
            document.getElementById(`btn-${gender}`).classList.add('active');
            updateMenuState();
        }

        function setEngine(engine) {
            playClickSound();
            if (detectOS() === 'Android' && currentLang === 'bn' && engine === 'cloud') return; 
            prefEngine = engine;
            document.getElementById('btn-cloud').classList.remove('active');
            document.getElementById('btn-offline').classList.remove('active');
            document.getElementById(`btn-${engine}`).classList.add('active');
            updateMenuState();
        }

        function speak(text, isLetter = false) {
            if (!text || text === '') return;
            let langCode = currentLang === 'en' ? 'en' : 'bn';

            if (detectOS() === 'Android' && currentLang === 'bn') {
                playOffline(text, langCode, isLetter);
                return;
            }

            if (prefEngine === 'cloud' && navigator.onLine) {
                try {
                    onlineAudio.pause();
                    onlineAudio.currentTime = 0;
                    const encodedText = encodeURIComponent(text);
                    const url = `https://translate.google.com/translate_tts?ie=UTF-8&client=tw-ob&tl=${langCode}&q=${encodedText}`;
                    
                    onlineAudio.src = url;
                    onlineAudio.playbackRate = isLetter ? 0.9 : 0.75; 
                    
                    let playPromise = onlineAudio.play();
                    if (playPromise !== undefined) {
                        playPromise.catch(error => {
                            playOffline(text, langCode, isLetter); 
                        });
                    }
                } catch(e) {
                    playOffline(text, langCode, isLetter);
                }
            } else {
                playOffline(text, langCode, isLetter);
            }
        }

        function playOffline(text, langCode, isLetter = false) {
            if (!synth) return;
            try {
                if (synth.speaking) synth.cancel();
                
                let selectedVoice = getOfflineVoice(langCode, prefGender);
                const utterThis = new SpeechSynthesisUtterance(text);
                
                if (selectedVoice) {
                    utterThis.voice = selectedVoice;
                    utterThis.lang = selectedVoice.lang;
                } else {
                    utterThis.lang = langCode === 'bn' ? 'bn-BD' : 'en-US';
                }
                
                utterThis.rate = isLetter ? 0.85 : 0.7; 
                synth.speak(utterThis);
            } catch(e) {}
        }

        const layouts = {
            en: {
                alpha: [
                    ['1','2','3','4','5','6','7','8','9','0'],
                    ['Q','W','E','R','T','Y','U','I','O','P'],
                    ['A','S','D','F','G','H','J','K','L'],
                    ['Z','X','C','V','B','N','M',',','.','?']
                ],
                sym: [
                    ['!','@','#','$','%','^','&','*','(',')'],
                    ['-','_','=','+','[',']','{','}','\\','|'],
                    [';',':','\'','"',',','.','<','>','/','?']
                ]
            },
            bn: {
                cons: [
                    ['ক','খ','গ','ঘ','ঙ','চ','ছ','জ','ঝ','ঞ'],
                    ['ট','ঠ','ড','ঢ','ণ','ত','থ','দ','ধ','ন'],
                    ['প','ফ','ব','ভ','ম','য','র','ল','শ','ষ'],
                    ['স','হ','ড়','ঢ়','য়','ৎ','ং','ঃ','ঁ'],
                    ['া','ি','ী','ু','ূ','ৃ','ে','ৈ','ো','ৌ']
                ],
                vowels: [
                    ['০','১','২','৩','৪','৫','৬','৭','৮','৯'],
                    ['অ','আ','ই','ঈ','উ','ঊ','ঋ','এ','ঐ','ও','ঔ'],
                    ['া','ি','ী','ু','ূ','ৃ','ে','ৈ','ো','ৌ']
                ]
            }
        };

        const medicalPhrases = {
            en: [
                { t: "I need suction", v: "I need suction to clear my throat." },
                { t: "I am in pain", v: "I am in pain, please help me." },
                { t: "I can't breathe", v: "I am having trouble breathing." },
                { t: "Adjust position", v: "Please adjust my sitting position." },
                { t: "I want Water", v: "I am thirsty, I need water." },
                { t: "Call Nurse", v: "Please call the nurse immediately." },
                { t: "YES", v: "Yes." },
                { t: "NO", v: "No." }
            ],
            bn: [
                { t: "সাকশন দরকার", v: "আমার সাকশন দরকার।" },
                { t: "ব্যথা করছে", v: "আমার খুব ব্যথা করছে।" },
                { t: "শ্বাসকষ্ট হচ্ছে", v: "আমার শ্বাস নিতে কষ্ট হচ্ছে।" },
                { t: "অবস্থান বদলান", v: "আমাকে একটু সোজা করে দিন।" },
                { t: "পানি খাব", v: "আমি পানি খাবো।" },
                { t: "নার্সকে ডাকুন", v: "দয়া করে নার্সকে ডাকুন।" },
                { t: "হ্যাঁ", v: "হ্যাঁ।" },
                { t: "না", v: "না।" }
            ]
        };

        function resetClearTimer() {
            if (clearTimer) clearTimeout(clearTimer);
            clearTimer = setTimeout(() => { clearText(); }, 3000);
        }

        function cancelClearTimer() {
            if (clearTimer) { clearTimeout(clearTimer); clearTimer = null; }
        }

        function playMedicalPhrase(phraseObj) {
            playClickSound();
            cancelClearTimer();
            sentence = phraseObj.t;
            display.innerText = sentence;
            speak(phraseObj.v, false);
            resetClearTimer(); 
        }

        function appendChar(char) {
            playClickSound();
            cancelClearTimer(); 
            sentence += char;
            display.innerText = sentence;
            if(char === " ") speak("Space", true);
            else speak(char, true);
        }

        function backspace() {
            playClickSound();
            cancelClearTimer();
            sentence = sentence.slice(0, -1);
            display.innerText = sentence;
            speak("Delete", true);
        }

        function clearText() {
            playClickSound();
            cancelClearTimer();
            sentence = "";
            display.innerText = sentence;
        }

        function speakFullText() {
            playClickSound();
            if(sentence.trim() !== "") {
                speak(sentence, false);
                resetClearTimer(); 
            }
        }

        function toggleLanguage() {
            currentLang = currentLang === 'en' ? 'bn' : 'en';
            currentTab = currentLang === 'en' ? 'alpha' : 'cons';
            
            const btn = document.getElementById('lang-btn');
            if (btn) btn.innerText = currentLang === 'en' ? "🌐 Switch to বাংলা" : "🌐 Switch to English";
            
            if (detectOS() === 'Android' && currentLang === 'bn') {
                prefEngine = 'offline';
            }

            updateMenuState();
            renderUI();
        }

        function setTab(tabId) {
            playClickSound();
            currentTab = tabId;
            renderUI();
        }

        function renderUI() {
            const tabsContainer = document.getElementById('tabs-container');
            const kbContainer = document.getElementById('keyboard');
            const medicalTray = document.getElementById('medical-tray');
            if(!tabsContainer) return;
            
            tabsContainer.innerHTML = '';
            kbContainer.innerHTML = '';
            medicalTray.innerHTML = '';

            const tabs = currentLang === 'en' 
                ? [ {id:'alpha', label:'ABC / 123'}, {id:'sym', label:'Symbols'} ]
                : [ {id:'cons', label:'কখগ (Consonants)'}, {id:'vowels', label:'অআ & ১২৩ (Vowels/Numbers)'} ];

            tabs.forEach(t => {
                const btn = document.createElement('button');
                btn.className = `tab-btn ${currentTab === t.id ? 'active' : ''}`;
                btn.innerText = t.label;
                btn.onclick = () => setTab(t.id);
                tabsContainer.appendChild(btn);
            });

            const layout = layouts[currentLang][currentTab];
            layout.forEach(row => {
                const rowDiv = document.createElement('div');
                rowDiv.className = 'key-row';
                row.forEach(key => {
                    const btn = document.createElement('button');
                    btn.className = 'key-char';
                    btn.innerText = key;
                    btn.onclick = () => appendChar(key);
                    rowDiv.appendChild(btn);
                });
                kbContainer.appendChild(rowDiv);
            });

            const bottomRow = document.createElement('div');
            bottomRow.className = 'key-row';
            const spaceBtn = document.createElement('button');
            spaceBtn.className = 'key-space';
            spaceBtn.innerText = currentLang === 'en' ? 'SPACE' : 'স্পেস (SPACE)';
            spaceBtn.onclick = () => appendChar(' ');
            bottomRow.appendChild(spaceBtn);
            kbContainer.appendChild(bottomRow);

            const phrases = medicalPhrases[currentLang];
            phrases.forEach(phrase => {
                const btn = document.createElement('button');
                btn.className = 'phrase-btn';
                btn.innerText = phrase.t;
                
                const fillBar = document.createElement('div');
                fillBar.className = 'dwell-progress';
                btn.appendChild(fillBar);

                let startTime = 0;
                let animFrame = null;

                btn.onclick = () => playMedicalPhrase(phrase);

                btn.onmouseenter = () => {
                    startTime = Date.now();
                    const duration = 5000; 

                    function updateProgress() {
                        let elapsed = Date.now() - startTime;
                        let pct = (elapsed / duration) * 100;
                        if (pct > 100) pct = 100;
                        fillBar.style.width = pct + '%';

                        if (elapsed < duration) {
                            animFrame = requestAnimationFrame(updateProgress);
                        } else {
                            playMedicalPhrase(phrase);
                            resetDwell();
                        }
                    }
                    animFrame = requestAnimationFrame(updateProgress);
                };

                btn.onmouseleave = () => {
                    resetDwell();
                };

                function resetDwell() {
                    if (animFrame) cancelAnimationFrame(animFrame);
                    fillBar.style.width = '0%';
                }

                medicalTray.appendChild(btn);
            });
        }

        var gateway = `ws://${window.location.hostname}:81/`;
        function initWebSocket() {
            var websocket = new WebSocket(gateway);
            websocket.onopen = () => {
                const bar = document.querySelector('.status-bar');
                if(bar) bar.classList.add('connected');
                const status = document.getElementById('ws-status');
                if(status) status.innerText = "CogniLink Linked";
            };
            websocket.onclose = () => {
                const bar = document.querySelector('.status-bar');
                if(bar) bar.classList.remove('connected');
                const status = document.getElementById('ws-status');
                if(status) status.innerText = "CogniLink Disconnected";
                setTimeout(initWebSocket, 2000);
            };
            websocket.onmessage = (event) => {
                var data = JSON.parse(event.data);
                var batElement = document.getElementById('bat');
                if(batElement) {
                    batElement.innerHTML = data.bat + "%";
                    if(data.bat <= 20) batElement.style.color = "var(--danger)";
                    else if(data.bat <= 50) batElement.style.color = "var(--warning)";
                    else batElement.style.color = "var(--success)";
                }
            };
        }

        document.addEventListener('click', function(event) {
            const menu = document.getElementById('settings-menu');
            const icon = document.querySelector('.settings-icon');
            if (menu && menu.classList.contains('open') && !menu.contains(event.target) && !icon.contains(event.target)) {
                menu.classList.remove('open');
            }
        });

        window.addEventListener('load', () => {
            initWebSocket();
            if (synth && synth.onvoiceschanged !== undefined) {
                synth.onvoiceschanged = () => {
                    getVoicesSafe();
                    updateMenuState();
                };
            }
            renderUI(); 
            updateMenuState();
        });
    </script>
</body>
</html>
)=====";

#endif