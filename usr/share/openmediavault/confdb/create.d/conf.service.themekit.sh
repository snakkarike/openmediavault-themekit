#!/bin/sh

set -e

. /usr/share/openmediavault/scripts/helper-functions

if ! omv_config_exists "/config/services/themekit"; then
    omv_config_add_node "/config/services" "themekit"

    omv_config_add_key "/config/services/themekit" "theme" "default"
    omv_config_add_key "/config/services/themekit" "accent" "default"
    omv_config_add_key "/config/services/themekit" "accentSpecialPages" "false" "bool"
    omv_config_add_key "/config/services/themekit" "enableTypography" "false" "bool"
    omv_config_add_key "/config/services/themekit" "enableCustomCss" "false" "bool"
    omv_config_add_key "/config/services/themekit" "baseFontSize" "16" "integer"
    omv_config_add_key "/config/services/themekit" "customFont" ""
    omv_config_add_key "/config/services/themekit" "customCss" ""
fi

exit 0
