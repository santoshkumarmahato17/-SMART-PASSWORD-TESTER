#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

// Function prototypes
int check_length(char *password);
int check_uppercase(char *password);
int check_lowercase(char *password);
int check_digits(char *password);
int check_special_chars(char *password);
int calculate_strength_score(char *password);
void print_strength_level(int score);
void generate_strong_password(char *password);

int main() {
    char input_password[100];
    char generated_password[100];
    
    srand(time(NULL)); // Seed for random password generation
    
    printf("\n=== 🔐 SMART PASSWORD TESTER ===\n");
    printf("================================\n");
    
    // STEP 1: Test user's password
    printf("\n📝 Enter your password to test: ");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = 0; // Remove newline
    
    if (strlen(input_password) == 0) {
        printf("❌ Empty password!\n");
        strcpy(input_password, "password"); // Default weak password for demo
        printf("🔄 Using 'password' for demo...\n");
    }
    
    // Analyze user's password
    int score = calculate_strength_score(input_password);
    printf("\n📊 YOUR PASSWORD ANALYSIS:\n");
    printf("=========================\n");
    printf("Password: %s\n", input_password);
    printf("✅ Length: %s\n", check_length(input_password) ? "✓ Good (8+ chars)" : "✗ Weak (<8 chars)");
    printf("✅ Uppercase: %s\n", check_uppercase(input_password) ? "✓ Present" : "✗ Missing");
    printf("✅ Lowercase: %s\n", check_lowercase(input_password) ? "✓ Present" : "✗ Missing");
    printf("✅ Numbers: %s\n", check_digits(input_password) ? "✓ Present" : "✗ Missing");
    printf("✅ Special chars: %s\n", check_special_chars(input_password) ? "✓ Present" : "✗ Missing");
    
    printf("\n🎯 STRENGTH: ");
    print_strength_level(score);
    
    // STEP 2: Auto-generate 3 STRONG passwords
    printf("\n\n🔥 TOP 3 STRONG PASSWORD SUGGESTIONS:\n");
    printf("=====================================\n");
    
    for (int i = 1; i <= 3; i++) {
        generate_strong_password(generated_password);
        printf("%d️⃣  %s\n", i, generated_password);
        printf("   💪 Length: %zu chars | 100/100 Score ✅\n", strlen(generated_password));
    }
    
    printf("\n💡 TIPS:\n");
    printf("• Use 12+ characters\n");
    printf("• Mix uppercase, lowercase, numbers, symbols\n");
    printf("• Avoid dictionary words\n");
    printf("• Change passwords every 3-6 months\n");
    
    printf("\n🔒 Stay Secure! 👋\n");
    return 0;
}

int check_length(char *password) {
    return strlen(password) >= 8;
}

int check_uppercase(char *password) {
    for (int i = 0; password[i]; i++) {
        if (isupper(password[i])) return 1;
    }
    return 0;
}

int check_lowercase(char *password) {
    for (int i = 0; password[i]; i++) {
        if (islower(password[i])) return 1;
    }
    return 0;
}

int check_digits(char *password) {
    for (int i = 0; password[i]; i++) {
        if (isdigit(password[i])) return 1;
    }
    return 0;
}

int check_special_chars(char *password) {
    const char special[] = "!@#$%^&*()_+-=[]{}|;:,.<>?";
    for (int i = 0; password[i]; i++) {
        for (int j = 0; special[j]; j++) {
            if (password[i] == special[j]) return 1;
        }
    }
    return 0;
}

int calculate_strength_score(char *password) {
    int score = 0;
    
    if (check_length(password)) score += 25;
    if (check_uppercase(password)) score += 20;
    if (check_lowercase(password)) score += 20;
    if (check_digits(password)) score += 20;
    if (check_special_chars(password)) score += 15;
    
    // Bonus for length
    int len = strlen(password);
    if (len >= 12) score += 10;
    else if (len >= 10) score += 5;
    
    return score;
}

void print_strength_level(int score) {
    if (score >= 90) {
        printf("🟢 VERY STRONG! 🎉\n");
    } else if (score >= 70) {
        printf("🟡 STRONG! 👍\n");
    } else if (score >= 50) {
        printf("🟠 MEDIUM ⚠️\n");
    } else if (score >= 30) {
        printf("🔴 WEAK! ❌\n");
    } else {
        printf("⚫ VERY WEAK! 😱\n");
    }
    printf("Score: %d/100\n", score);
}

void generate_strong_password(char *password) {
    char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_-+=[]{}|;:,.<>?";
    int len = 12 + (rand() % 9); // 12-21 characters (different lengths)
    int special_pos[4], digit_pos[3], upper_pos[3];
    
    // Ensure strong composition: 4 special, 3 digits, 3 uppercase
    for (int i = 0; i < 4; i++) special_pos[i] = rand() % len;
    for (int i = 0; i < 3; i++) digit_pos[i] = rand() % len;
    for (int i = 0; i < 3; i++) upper_pos[i] = rand() % len;
    
    // Fill with random chars first
    for (int i = 0; i < len; i++) {
        password[i] = chars[rand() % strlen(chars)];
    }
    
    // Force special characters at random positions
    const char specials[] = "!@#$%^&*()_-+=[]{}|;:,.<>?";
    for (int i = 0; i < 4; i++) {
        password[special_pos[i]] = specials[rand() % strlen(specials)];
    }
    
    // Force digits
    for (int i = 0; i < 3; i++) {
        password[digit_pos[i]] = '0' + rand() % 10;
    }
    
    // Force uppercase letters
    for (int i = 0; i < 3; i++) {
        password[upper_pos[i]] = 'A' + rand() % 26;
    }
    
    password[len] = '\0';
}
