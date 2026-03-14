<h1>🔐 Smart Password Tester - C Mini Project</h1>
📋 Project Overview
A lightweight, production-ready C program that instantly analyzes your password strength and automatically generates 3 unique, ultra-strong passwords with 100/100 scores. No menus, no hassle - just enter and get results!

<h1>✨ Key Features</h1>
Feature                  Description
🚀 Instant Analysis     Tests length, uppercase, lowercase, digits, special chars
🎯 Strength Scoring     0-100 score with 5 color-coded levels (Very Weak → Very Strong)
🔥 Auto Suggestions     Generates 3 different strong passwords (12-21 chars) every run
✅ Guaranteed Strong    All suggestions have **4+ special chars, 3+ digits, 3+ uppercase
💡 Security Tips        Built-in best practices guide
⚡ One-Shot Flow        Enter password → Analysis → 3 suggestions → Done!

🟢 Strength Levels
1.🟢 VERY STRONG (90-100): All criteria + 12+ chars
2.🟡 STRONG (70-89): Most criteria + 10+ chars  
3.🟠 MEDIUM (50-69): Some criteria + 8+ chars
4.🔴 WEAK (30-49): Basic requirements missing
5.⚫ VERY WEAK (<30): Too simple!

📊 Scoring Algorithm
Length (8+)     → +25 pts
Uppercase       → +20 pts  
Lowercase       → +20 pts
Digits          → +20 pts
Special Chars   → +15 pts
Length Bonus    → +5-10 pts
**MAX: 100/100**

<h1>🎮 How It Works</h1>h1>
1. Enter any password (or press Enter for demo)
2. Get detailed analysis + strength score
3. Receive 3 AUTO-GENERATED strong passwords
4. Copy & use securely! 🔒

🖥️ Sample Output
📝 Enter your password to test: password123

📊 YOUR PASSWORD ANALYSIS:
Password: password123
✅ Length: ✓ Good (8+ chars)  
✅ Uppercase: ✗ Missing
✅ Lowercase: ✓ Present
✅ Numbers: ✓ Present
✅ Special chars: ✗ Missing

🎯 STRENGTH: 🟠 MEDIUM ⚠️
Score: 65/100

🔥 TOP 3 STRONG PASSWORD SUGGESTIONS:
1️⃣  K9#mP4$xL7#Q2vN8jT    💪 16 chars | 100/100
2️⃣  @3WpR6!hT9*mN2xB5    💪 14 chars | 100/100  
3️⃣  X8#vL2$kP7@nM4xQ9    💪 15 chars | 100/100
