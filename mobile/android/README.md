# Android Application

A simple Android application demonstrating mobile build automation.

## Features

- Android SDK 34
- Material Design
- Gradle build system
- Automated CI/CD

## Building

```bash
# Build debug APK
./gradlew assembleDebug

# Build release APK
./gradlew assembleRelease

# Run tests
./gradlew test

# Install on device
./gradlew installDebug
```

## Release Signing

For production releases, configure signing in `app/build.gradle`:

### Local Development

1. Create a keystore:
   ```bash
   keytool -genkey -v -keystore release.keystore -alias build-systems \
     -keyalg RSA -keysize 2048 -validity 10000
   ```

2. Add to `~/.gradle/gradle.properties`:
   ```properties
   RELEASE_STORE_FILE=/path/to/release.keystore
   RELEASE_STORE_PASSWORD=your_password
   RELEASE_KEY_ALIAS=build-systems
   RELEASE_KEY_PASSWORD=your_password
   ```

### CI/CD Signing (GitHub Actions)

**IMPORTANT**: Never commit keystores to the repository!

Use GitHub Secrets to store signing credentials:

1. **Encode keystore to base64**:
   ```bash
   base64 -i release.keystore | pbcopy  # macOS
   base64 -w 0 release.keystore         # Linux
   ```

2. **Add GitHub Secrets**:
   - `KEYSTORE_BASE64`: Base64-encoded keystore file
   - `KEYSTORE_PASSWORD`: Keystore password
   - `KEY_ALIAS`: Key alias (e.g., "build-systems")
   - `KEY_PASSWORD`: Key password

3. **Example CI workflow step**:
   ```yaml
   - name: Decode keystore
     run: |
       echo "${{ secrets.KEYSTORE_BASE64 }}" | base64 --decode > release.keystore
   
   - name: Build signed APK
     env:
       RELEASE_STORE_FILE: ../release.keystore
       RELEASE_STORE_PASSWORD: ${{ secrets.KEYSTORE_PASSWORD }}
       RELEASE_KEY_ALIAS: ${{ secrets.KEY_ALIAS }}
       RELEASE_KEY_PASSWORD: ${{ secrets.KEY_PASSWORD }}
     run: ./gradlew assembleRelease
   
   - name: Clean up keystore
     if: always()
     run: rm -f release.keystore
   ```

### Build Configuration

Add to `app/build.gradle`:

```gradle
android {
    signingConfigs {
        release {
            storeFile file(System.getenv("RELEASE_STORE_FILE") ?: "release.keystore")
            storePassword System.getenv("RELEASE_STORE_PASSWORD")
            keyAlias System.getenv("RELEASE_KEY_ALIAS")
            keyPassword System.getenv("RELEASE_KEY_PASSWORD")
        }
    }
    
    buildTypes {
        release {
            signingConfig signingConfigs.release
            minifyEnabled true
            proguardFiles getDefaultProguardFile('proguard-android-optimize.txt'), 'proguard-rules.pro'
        }
    }
}
```

## Requirements

- Android SDK 34
- Gradle 8.2+
- JDK 11+

## Security Best Practices

- ✅ Never commit keystores or passwords
- ✅ Use environment variables for credentials
- ✅ Store keystore securely (password manager, vault)
- ✅ Use different keys for debug/release builds
- ✅ Enable ProGuard/R8 for release builds
- ✅ Clean up temporary keystores in CI

