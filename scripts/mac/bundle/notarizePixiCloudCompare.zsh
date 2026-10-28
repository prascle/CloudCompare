APP_PATH="/Users/paul/projets/CloudCompare/CloudCompare/.build/install/CloudCompare"
NOWIS=`date "+%Y%m%d_%H%M%S"`
ZIP_PATH="/Users/paul/projets/CloudCompare/CloudCompare/.build/install/CloudCompare_$NOWIS.zip"
DMG="/Users/paul/projets/CloudCompare/CloudCompare/.build/install/CloudCompare_$NOWIS.dmg"

# --- notarize and staple cloudCompare.app
#     - Create a ZIP archive suitable for notarization.
#     - submit for notarization
#     - staple the app: message "The staple and validate action worked!"

/usr/bin/ditto -c -k -v --keepParent "$APP_PATH" "$ZIP_PATH"
xcrun notarytool submit "$ZIP_PATH" --keychain-profile "AC_PASSWORD" --wait
xcrun stapler staple ${APP_PATH}/CloudCompare.app

# --- notarize and staple cloudCompare.dmg
#     - Create a disk image (dmg) from our disk image root directory.
#     - submit for notarization
#     - staple the dmg: message "The staple and validate action worked!"

hdiutil create -ov -srcFolder "${APP_PATH}" -quiet -o "${DMG}"
xcrun notarytool submit "${DMG}" --keychain-profile "AC_PASSWORD" --wait
xcrun stapler staple ${DMG}

# --- Controle de staple

xcrun stapler validate ${DMG}

# --- somme de controle

shasum -a 256 ${DMG}
