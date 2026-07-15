<?php
/**
 * ThemeKit RPC service.
 *
 * Exposes ThemeKit.get / ThemeKit.set to the web UI. Reads and writes the
 * conf.service.themekit config object, then asks Salt to regenerate the
 * CSS.
 */

use OMV\Config\Database;

class OMVRpcServiceThemeKit extends \OMV\Rpc\ServiceAbstract
{
    public function getName()
    {
        return "ThemeKit";
    }

    public function initialize()
    {
        $this->registerMethod("get");
        $this->registerMethod("set");
    }

    public function get($params, $context)
    {
        $this->validateMethodContext($context, [
            "role" => OMV_ROLE_ADMINISTRATOR
        ]);

        $db = Database::getInstance();
        $object = $db->get("conf.service.themekit");
        $assoc = $object->getAssoc();
        
        
        return $assoc;
    }

    public function set($params, $context)
    {
        $this->validateMethodContext($context, [
            "role" => OMV_ROLE_ADMINISTRATOR
        ]);



        $db = Database::getInstance();
        $object = $db->get("conf.service.themekit");
        
        // Merge the incoming parameters with the existing configuration to prevent wiping out fields
        // from other tabs when submitting a partial form (e.g. saving Typography without Settings)
        $existing = $object->getAssoc();
        $merged = array_merge($existing, $params);
        
        $object->setAssoc($merged);
        $db->set($object);

        // Re-render CSS via the salt state for this plugin.
        // We run this in the background so it doesn't block the RPC response!
        // We also sleep for 2 seconds to ensure omv-engined has finished writing the new config to disk.
        exec("(sleep 2; omv-salt deploy run themekit) > /dev/null 2>&1 &");

        return $object->getAssoc();
    }
}
