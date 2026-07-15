<?php
/**
 * ThemeKit Engine Module.
 *
 * Provides the module definition so omv-engined can trigger omv-salt
 * deploy run themekit when applied.
 */

namespace Engined\Module;

use OMV\Engine\Module\ServiceAbstract;

class ThemeKit extends ServiceAbstract
{
    public function getName()
    {
        return "themekit";
    }
}
