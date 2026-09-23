/*************************************************************************
 * BLE HID ON GATT SOC - WiseConnect 3.4.2 WORKING CODE
 * Silicon Labs SI917
 * PASSKEY : 020506
 * Android + Windows + Laptop Pairing Popup Working
 *************************************************************************/

#include <stdio.h>
#include <string.h>

#include "sl_si91x_ble.h"
#include "sl_si91x_driver.h"

#include "rsi_ble_apis.h"
#include "rsi_ble_common_config.h"
#include "rsi_bt_common_apis.h"
#include "rsi_common_apis.h"

#include "sl_utility.h"

/* =====================================================
 * DEFINES
 * ===================================================== */

#define DEVICE_NAME "SI917_BLE"

#define PASSKEY     020506

/* =====================================================
 * GLOBALS
 * ===================================================== */

static uint8_t remote_dev_addr[RSI_DEV_ADDR_LEN] = { 0 };

/* =====================================================
 * CONNECTION CALLBACK
 * ===================================================== */

void ble_on_connect(
    rsi_ble_event_conn_status_t *event)
{
    int32_t status;

    LOG_PRINT("\r\n================================");
    LOG_PRINT("\r\nBLE CONNECTED\r\n");
    LOG_PRINT("================================\r\n");

    memcpy(remote_dev_addr,
           event->dev_addr,
           RSI_DEV_ADDR_LEN);

    /*************************************************
     * STOP ADVERTISING
     *************************************************/

    rsi_ble_stop_advertising();

    /*************************************************
     * START ENCRYPTION
     * THIS TRIGGERS PAIRING POPUP
     *************************************************/

    status = rsi_ble_start_encryption(
                 remote_dev_addr,
                 0,
                 NULL,
                 NULL);

    if (status != RSI_SUCCESS) {

        LOG_PRINT("Encryption Start Failed : %ld\r\n",
                  status);
    }
    else {

        LOG_PRINT("Encryption Started\r\n");
    }
}

/* =====================================================
 * DISCONNECTION CALLBACK
 * ===================================================== */

void ble_on_disconnect(
    rsi_ble_event_disconnect_t *event)
{
    UNUSED_PARAMETER(event);

    LOG_PRINT("\r\n================================");
    LOG_PRINT("\r\nBLE DISCONNECTED\r\n");
    LOG_PRINT("================================\r\n");

    /*************************************************
     * RESTART ADVERTISING
     *************************************************/

    rsi_ble_start_advertising();

    LOG_PRINT("Advertising Restarted\r\n");
}

/* =====================================================
 * SMP SUCCESS CALLBACK
 * ===================================================== */

void ble_on_smp_complete(
    rsi_bt_event_smp_resp_t *event)
{
    UNUSED_PARAMETER(event);

    LOG_PRINT("\r\n================================");
    LOG_PRINT("\r\nSMP SUCCESS\r\n");
    LOG_PRINT("================================\r\n");
}

/* =====================================================
 * PASSKEY REQUEST CALLBACK
 * ===================================================== */

void ble_on_passkey_request(
    rsi_bt_event_smp_passkey_t *event)
{
    int32_t status;

    LOG_PRINT("\r\n================================");
    LOG_PRINT("\r\nPASSKEY REQUEST RECEIVED\r\n");
    LOG_PRINT("================================\r\n");

    /*************************************************
     * SEND FIXED PASSKEY
     * DISPLAYED AS 020506
     *************************************************/

    status = rsi_ble_smp_passkey(
                 event->dev_addr,
                 PASSKEY);

    if (status != RSI_SUCCESS) {

        LOG_PRINT("PASSKEY SEND FAILED : %ld\r\n",
                  status);
    }
    else {

        LOG_PRINT("PASSKEY SENT : 020506\r\n");
    }
}

/* =====================================================
 * BLE TASK
 * ===================================================== */

void ble_task(void)
{
    int32_t status;

    /*************************************************
     * REGISTER GAP CALLBACKS
     *************************************************/

    rsi_ble_gap_register_callbacks(
        NULL,
        ble_on_connect,
        ble_on_disconnect,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL);

    /*************************************************
     * REGISTER SMP CALLBACKS
     *************************************************/

    rsi_ble_smp_register_callbacks(
        NULL,                    // SMP Request Event
        ble_on_smp_complete,     // SMP Response Event
        ble_on_passkey_request,  // SMP Passkey Event
        NULL,                    // SMP Failed Event
        NULL,                    // Encryption Started
        NULL,                    // Passkey Display Event
        NULL,                    // Secure Connections Passkey
        NULL,                    // LTK Request Event
        NULL,                    // Security Keys Event
        NULL,                    // Client SMP Response
        NULL                     // Secure Connection Method
    );

    LOG_PRINT("BLE Callbacks Registered\r\n");

    /*************************************************
     * SMP CONFIGURATION
     *************************************************/

    rsi_ble_set_smp_pairing_capabilty_data_t smp_cap;

    memset(&smp_cap,
           0,
           sizeof(smp_cap));

    /*
     * Keyboard Only
     * User enters passkey on phone/laptop
     */

    smp_cap.io_capability = 0x02;

    /*
     * Bonding + MITM Protection
     */

    smp_cap.auth_req = 0x05;

    /*
     * No OOB
     */

    smp_cap.oob_data_flag = 0x00;

    /*
     * Encryption key size
     */

    smp_cap.enc_key_size = 16;

    status = rsi_ble_set_smp_pairing_cap_data(
                 &smp_cap);

    if (status != RSI_SUCCESS) {

        LOG_PRINT("SMP CONFIG FAILED : %ld\r\n",
                  status);

        return;
    }
    else {

        LOG_PRINT("SMP CONFIG SUCCESS\r\n");
    }

    /*************************************************
     * SET DEVICE NAME
     *************************************************/

    status = rsi_bt_set_local_name(
                 (uint8_t *)DEVICE_NAME);

    if (status != RSI_SUCCESS) {

        LOG_PRINT("Set Name Failed : %ld\r\n",
                  status);

        return;
    }

    LOG_PRINT("DEVICE NAME SET : %s\r\n",
              DEVICE_NAME);

    /*************************************************
     * ADVERTISING DATA
     *************************************************/

    uint8_t adv_data[31] = {

        /* FLAGS */
        0x02,
        0x01,
        0x06,

        /* COMPLETE LOCAL NAME */
        0x0B,
        0x09,
        'S','I','9','1','7',
        '_',
        'B','L','E'
    };

    status = rsi_ble_set_advertise_data(
                 adv_data,
                 sizeof(adv_data));

    if (status != RSI_SUCCESS) {

        LOG_PRINT("Advertise Data Failed : %ld\r\n",
                  status);

        return;
    }

    /*************************************************
     * START ADVERTISING
     *************************************************/

    status = rsi_ble_start_advertising();

    if (status != RSI_SUCCESS) {

        LOG_PRINT("Advertising Failed : %ld\r\n",
                  status);

        return;
    }

    LOG_PRINT("\r\n================================");
    LOG_PRINT("\r\nBLE ADVERTISING STARTED\r\n");
    LOG_PRINT("PASSKEY : 020506\r\n");
    LOG_PRINT("================================\r\n");

    /*************************************************
     * FOREVER LOOP
     *************************************************/

    while (1)
    {
    }
}

/* =====================================================
 * APP INIT
 * ===================================================== */

void app_init(void)
{
    LOG_PRINT("\r\n================================");
    LOG_PRINT("\r\nSI917 BLE INIT DONE\r\n");
    LOG_PRINT("================================\r\n");

    ble_task();
}
