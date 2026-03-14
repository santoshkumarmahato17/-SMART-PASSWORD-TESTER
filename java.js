class PasswordTester {
    constructor() {
        this.initializeElements();
        this.bindEvents();
    }

    initializeElements() {
        this.passwordInput = document.getElementById('passwordInput');
        this.toggleBtn = document.getElementById('toggleVisibility');
        this.analyzeBtn = document.getElementById('analyzeBtn');
        this.analysisSection = document.getElementById('analysisSection');
        this.suggestionsSection = document.getElementById('suggestionsSection');
        this.generateMoreBtn = document.getElementById('generateMoreBtn');
        
        this.statusElements = {
            length: document.getElementById('lengthStatus'),
            uppercase: document.getElementById('uppercaseStatus'),
            lowercase: document.getElementById('lowercaseStatus'),
            digits: document.getElementById('digitsStatus'),
            special: document.getElementById('specialStatus')
        };
        
        this.scoreElements = {
            circle: document.getElementById('scoreCircle'),
            value: document.getElementById('scoreValue'),
            label: document.getElementById('strengthLabel')
        };
    }

    bindEvents() {
        this.analyzeBtn.addEventListener('click', () => this.analyzePassword());
        this.passwordInput.addEventListener('keypress', (e) => {
            if (e.key === 'Enter') this.analyzePassword();
        });
        this.toggleBtn.addEventListener('click', () => this.toggleVisibility());
        this.generateMoreBtn.addEventListener('click', () => this.generatePasswords());
    }

    toggleVisibility() {
        const type = this.passwordInput.type === 'password' ? 'text' : 'password';
        this.passwordInput.type = type;
        const icon = this.toggleBtn.querySelector('i');
        icon.classList.toggle('fa-eye');
        icon.classList.toggle('fa-eye-slash');
    }

    async analyzePassword() {
        const password = this.passwordInput.value;
        if (!password) {
            alert('Please enter a password to analyze!');
            return;
        }

        // Show loading
        this.analyzeBtn.innerHTML = '<i class="fas fa-spinner fa-spin"></i> Analyzing...';
        this.analyzeBtn.disabled = true;

        try {
            // Call C backend via simulated API (or actual CGI in production)
            const result = await this.callBackend(password);
            
            this.displayAnalysis(result);
            this.generatePasswords();
            
            // Show sections
            this.analysisSection.classList.remove('hidden');
            this.suggestionsSection.classList.remove('hidden');
            
        } catch (error) {
            console.error('Analysis failed:', error);
            this.showError('Analysis failed. Using client-side fallback.');
            this.analyzeClientSide(password);
        } finally {
            this.analyzeBtn.innerHTML = '<i class="fas fa-magic"></i> Analyze';
            this.analyzeBtn.disabled = false;
        }
    }

    // Simulated backend call (replace with actual C CGI endpoint)
    async callBackend(password) {
        // In production: POST to /cgi-bin/password_tester.cgi
        // For demo: simulate with client-side logic matching C backend
        return new Promise((resolve) => {
            setTimeout(() => {
                resolve(this.simulateBackendAnalysis(password));
            }, 800);
        });
    }

    simulateBackendAnalysis(password) {
        return {
            length: password.length >= 8,
            uppercase: /[A-Z]/.test(password),
            lowercase: /[a-z]/.test(password),
            digits: /\d/.test(password),
            special: /[!@#$%^&*()_+\-=\$\${};':"\\|,.<>\/?]/.test(password),
            score: this.calculateScore(password)
        };
    }

    calculateScore(password) {
        let score = 0;
        if (password.length >= 8) score += 25;
        if (/[A-Z]/.test(password)) score += 20;
        if (/[a-z]/.test(password)) score += 20;
        if (/\d/.test(password)) score += 20;
        if (/[!@#$%^&*()_+\-=\$\${};':"\\|,.<>\/?]/.test(password)) score += 15;
        if (password.length >= 12) score += 10;
        else if (password.length >= 10) score += 5;
        return Math.min(score, 100);
    }

    displayAnalysis(result) {
        // Update criteria status
        Object.keys(this.statusElements).forEach(key => {
            const status = result[key];
            const element = this.statusElements[key];
            element.textContent = status ? '✓' : '✗';
            element.className = `status ${this.getStatusClass(result.score)}`;
        });

        // Update score
        this.scoreElements.value.textContent = result.score;
        this.scoreElements.circle.className = `score-circle ${this.getStatusClass(result.score)}`;
        this.scoreElements.label.textContent = this.getStrengthLabel(result.score);
        this.scoreElements.label.className = `strength-label strength-${this.getStrengthLevel(result.score)}`;
    }

    generatePasswords() {
        const container = document.getElementById('passwordSuggestions');
        container.innerHTML = '';

        for (let i = 1; i <= 3; i++) {
            const password = this.generateStrongPassword();
            const card = this.createPasswordCard(i, password);
            container.appendChild(card);
        }
    }

    generateStrongPassword() {
        const chars = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{}|;:,.<>?';
        const len = 12 + Math.floor(Math.random() * 10);
        let password = '';

        // Ensure strong composition
        const specials = '!@#$%^&*()_+-=[]{}|;:,.<>?';
        const positions = Array.from({length: len}, (_, i) => i);

        // Add 4 special chars
        for (let i = 0; i < 4; i++) {
            const pos = positions.splice(Math.floor(Math.random() * positions.length), 1)[0];
            password += specials[Math.floor(Math.random() * specials.length)];
        }

        // Add 3 digits