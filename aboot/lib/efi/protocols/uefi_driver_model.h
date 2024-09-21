#ifndef EFI_PROTOCOLS_UEFI_DRIVER_MODEL_H
#define EFI_PROTOCOLS_UEFI_DRIVER_MODEL_H

////
// EFI Driver Binding Protocol
///

#define EFI_DRIVER_BINDING_PROTOCOL_GUID {0x18a031ab,0xb443,0x4d1a, {0xa5,0xc0,0x0c,0x09,0x26,0x1e,0x9f,0x71}}

typedef struct _EFI_DRIVER_BINDING_PROTOCOL EFI_DRIVER_BINDING_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_BINDING_PROTOCOL_SUPPORTED)(
	IN EFI_DRIVER_BINDING_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_BINDING_PROTOCOL_START)(
	IN EFI_DRIVER_BINDING_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_BINDING_PROTOCOL_STOP)(
	IN EFI_DRIVER_BINDING_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN EFI_UINTN NumberOfChildren,
	IN EFI_DEVICE_PATH_PROTOCOL *ChildHandleBuffer OPTIONAL
);

typedef struct _EFI_DRIVER_BINDING_PROTOCOL {
	EFI_DRIVER_BINDING_PROTOCOL_SUPPORTED Supported;
	EFI_DRIVER_BINDING_PROTOCOL_START Start;
	EFI_DRIVER_BINDING_PROTOCOL_STOP Stop;
	EFI_UINT32 Version;
	EFI_HANDLE ImageHandle;
	EFI_HANDLE DriverBindingHandle;
} EFI_DRIVER_BINDING_PROTOCOL;


////
// EFI Platform Driver Override Protocol
///

#define EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GUID {0x6b30c738,0xa391,0x11d4, {0x9a,0x3b,0x00,0x90,0x27,0x3f,0xc1,0x4d}}

typedef struct _EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER)(
	IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN OUT EFI_HANDLE *DriverImageHandle
);

typedef
EFI_STATUS
(EFIAPI *EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER_PATH)(
	IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN OUT EFI_DEVICE_PATH_PROTOCOL **DriverImagePath
);

typedef
EFI_STATUS
(EFIAPI *EFI_PLATFORM_DRIVER_OVERRIDE_DRIVER_LOADED)(
	IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN EFI_DEVICE_PATH_PROTOCOL *DriverImagePath,
	IN EFI_HANDLE DriverImageHandle
);

typedef struct _EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL {
	EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER GetDriver;
	EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER_PATH GetDriverPath;
	EFI_PLATFORM_DRIVER_OVERRIDE_DRIVER_LOADED DriverLoaded;
} EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL;

////
// EFI Bus Specific Driver Override Protocol
///

#define EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_GUID {0x3bc1b285,0x8a15,0x4a82, {0xaa,0xbf,0x4d,0x7d,0x13,0xfb,0x32,0x65}}

typedef struct _EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_GET_DRIVER)(
	IN EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL *This,
	IN OUT EFI_HANDLE *DriverImageHandle
);

typedef struct _EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL {
	EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_GET_DRIVER GetDriver;
} EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL;

////
// EFI Driver Diagnostics Protocol
///

#define EFI_DRIVER_DIAGNOSTICS_PROTOCOL_GUID {0x4d330321,0x025f,0x4aac, {0x90,0xd8,0x5e,0xd9,0x00,0x17,0x3b,0x63}}

typedef struct _EFI_DRIVER_DIAGNOSTICS2_PROTOCOL EFI_DRIVER_DIAGNOSTICS2_PROTOCOL;

typedef enum {
	EfiDriverDiagnosticTypeStandard = 0,
	EfiDriverDiagnosticTypeExtended = 1,
	EfiDriverDiagnosticTypeManufacturing = 2,
	EfiDriverDiagnosticTypeCancel = 3,
	EfiDriverDiagnosticTypeMaximum
} EFI_DRIVER_DIAGNOSTIC_TYPE;

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_DIAGNOSTICS2_RUN_DIAGNOSTICS)(
	IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN EFI_HANDLE ChildHandle OPTIONAL,
	IN EFI_DRIVER_DIAGNOSTIC_TYPE DiagnosticType,
	IN CHAR8 *Language,
	OUT EFI_GUID **ErrorType,
	OUT EFI_UINTN *BufferSize,
	OUT CHAR16 **Buffer
);

typedef struct _EFI_DRIVER_DIAGNOSTICS2_PROTOCOL {
	EFI_DRIVER_DIAGNOSTICS2_RUN_DIAGNOSTICS RunDiagnostics;
	CHAR8 *SupportedLanguages;
} EFI_DRIVER_DIAGNOSTICS2_PROTOCOL;

////
// EFI Component Name Protocol
///

#define EFI_COMPONENT_NAME2_PROTOCOL_GUID {0x6a7a5cff,0xe8d9,0x4f70, {0xba,0xda,0x75,0xab,0x30,0x25,0xce,0x14}}

typedef struct _EFI_COMPONENT_NAME2_PROTOCOL EFI_COMPONENT_NAME2_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_COMPONENT_NAME_GET_DRIVER_NAME)(
	IN EFI_COMPONENT_NAME2_PROTOCOL *This,
	IN CHAR8 *Language,
	OUT CHAR16 **DriverName
);

typedef
EFI_STATUS
(EFIAPI *EFI_COMPONENT_NAME_GET_CONTROLLER_NAME)(
	IN EFI_COMPONENT_NAME2_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN EFI_HANDLE ChildHandle OPTIONAL,
	IN CHAR8 *Language,
	OUT CHAR16 **ControllerName
);

typedef struct _EFI_COMPONENT_NAME2_PROTOCOL {
	EFI_COMPONENT_NAME_GET_DRIVER_NAME GetDriverName;
	EFI_COMPONENT_NAME_GET_CONTROLLER_NAME GetControllerName;
	CHAR8 *SupportedLanguages;
} EFI_COMPONENT_NAME2_PROTOCOL;

////
// EFI Service Binding Protocol
///

typedef struct _EFI_SERVICE_BINDING_PROTOCOL EFI_SERVICE_BINDING_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_SERVICE_BINDING_CREATE_CHILD)(
	IN EFI_SERVICE_BINDING_PROTOCOL *This,
	IN OUT EFI_HANDLE *ChildHandle
);

typedef
EFI_STATUS
(EFIAPI *EFI_SERVICE_BINDING_DESTROY_CHILD)(
	IN EFI_SERVICE_BINDING_PROTOCOL *This,
	IN EFI_HANDLE ChildHandle
);

typedef struct _EFI_SERVICE_BINDING_PROTOCOL {
	EFI_SERVICE_BINDING_CREATE_CHILD CreateChild;
	EFI_SERVICE_BINDING_DESTROY_CHILD DestroyChild;
} EFI_SERVICE_BINDING_PROTOCOL;

////
// EFI Platform to Driver Configuration Protocol
///

#define EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_GUID {0x642cd590,0x8059,0x4c0a, {0xa9,0x58,0xc5,0xec,0x07,0xd2,0x3c,0x4b}}
#define EFI_PLATFORM_TO_DRIVER_CONFIGURATION_CLP_GUID {0x345ecc0e,0xcb6,0x4b75, {0xbb,0x57,0x1b,0x12,0x9c,0x47,0x33,0x3e}}

typedef struct _EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL;

typedef enum {
	EfiPlatformConfigurationActionNone = 0,
	EfiPlatformConfigurationActionStopController = 1,
	EfiPlatformConfigurationActionRestartController = 2,
	EfiPlatformConfigurationActionRestartPlatform = 3,
	EfiPlatformConfigurationActionNvramFailed = 4,
	EfiPlatformConfigurationActionUnsupportedGuid = 5,
	EfiPlatformConfigurationActionMaximum
} EFI_PLATFORM_CONFIGURATION_ACTION;

typedef struct {
	CHAR8 *CLPCommand;
	EFI_UINT32 CLPCommandLength;
	CHAR8 *CLPReturnString;
	EFI_UINT32 CLPReturnStringLength;
	EFI_UINT8 CLPCmdStatus;
	EFI_UINT8 CLPErrorValue;
	EFI_UINT16 CLPMsgCode;
} EFI_CONFIGURE_CLP_PARAMETER_BLK;

typedef
EFI_STATUS
(EFIAPI *EFI_PLATFORM_TO_DRIVER_CONFIGURATION_QUERY)(
	IN EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN EFI_HANDLE ChildHandle OPTIONAL,
	IN EFI_UINTN *Instance,
	OUT EFI_GUID **ParameterTypeGuid,
	OUT VOID **ParameterBlock,
	OUT EFI_UINTN *ParameterBlockSize
);

typedef
EFI_STATUS
(EFIAPI *EFI_PLATFORM_TO_DRIVER_CONFIGURATION_RESPONSE)(
	IN EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN EFI_HANDLE ChildHandle OPTIONAL,
	IN EFI_UINTN *Instance,
	IN EFI_GUID *ParameterTypeGuid,
	IN VOID *ParameterBlock,
	IN EFI_UINTN ParameterBlockSize,
	IN EFI_PLATFORM_CONFIGURATION_ACTION ConfigurationAction
);

typedef struct _EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL {
	EFI_PLATFORM_TO_DRIVER_CONFIGURATION_QUERY Query;
	EFI_PLATFORM_TO_DRIVER_CONFIGURATION_RESPONSE Response;
} EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL;

////
// EFI Driver Supported EFI Version Protocol
///

#define EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL_GUID {0x5c198761,0x16a8,0x4e69, {0x97,0x2c,0x89,0xd6,0x79,0x54,0xf8,0x1d}}

typedef struct _EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL;

typedef struct _EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL {
	EFI_UINT32 Length;
	EFI_UINT32 FirmwareVersion;
} EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL;

////
// EFI Driver Family Override Protocol
///

#define EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL_GUID {0xb1ee129e,0xda36,0x4181, {0x91,0xf8,0x04,0xa4,0x92,0x37,0x66,0xa7}}

typedef struct _EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL;

typedef
EFI_UINT32
(EFIAPI *EFI_DRIVER_FAMILY_OVERRIDE_GET_VERSION)(
	IN EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL *This
);

typedef struct _EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL {
	EFI_DRIVER_FAMILY_OVERRIDE_GET_VERSION GetVersion;
} EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL;

////
// EFI Driver Health Protocol
///

#define EFI_DRIVER_HEALTH_PROTOCOL_GUID {0x2a534210,0x9280,0x41d8, {0xae,0x79,0xca,0xda,0x01,0xa2,0xb1,0x27}}

typedef struct _EFI_DRIVER_HEALTH_PROTOCOL EFI_DRIVER_HEALTH_PROTOCOL;

typedef enum {
	EfiDriverHealthStatusHealthy,
	EfiDriverHealthStatusRepairRequired,
	EfiDriverHealthStatusConfigurationRequired,
	EfiDriverHealthStatusFailed,
	EfiDriverHealthStatusReconnectRequired,
	EfiDriverHealthStatusRebootRequired
} EFI_DRIVER_HEALTH_STATUS;

typedef struct {
	EFI_HII_HANDLE HiiHandle;
	EFI_STRING_ID StringId;
	EFI_UINT64 MessageCode;
} EFI_DRIVER_HEALTH_HII_MESSAGE;

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_HEALTH_GET_HEALTH_STATUS)(
	IN EFI_DRIVER_HEALTH_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle OPTIONAL,
	IN EFI_HANDLE ChildHandle OPTIONAL,
	OUT EFI_DRIVER_HEALTH_STATUS *HealthStatus,
	OUT EFI_DRIVER_HEALTH_HII_MESSAGE **MessageList OPTIONAL,
	OUT EFI_HII_HANDLE *FormHiiHandle OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_HEALTH_REPAIR_NOTIFY)(
	IN EFI_UINTN Value,
	IN EFI_UINTN Limit
);

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_HEALTH_REPAIR)(
	IN EFI_DRIVER_HEALTH_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN EFI_HANDLE ChildHandle OPTIONAL,
	IN EFI_DRIVER_HEALTH_REPAIR_NOTIFY RepairNotify OPTIONAL
);

typedef struct _EFI_DRIVER_HEALTH_PROTOCOL {
	EFI_DRIVER_HEALTH_GET_HEALTH_STATUS GetHealthStatus;
	EFI_DRIVER_HEALTH_REPAIR Repair;
} EFI_DRIVER_HEALTH_PROTOCOL;

////
// EFI Adapter Information Protocol
///

#define EFI_ADAPTER_INFORMATION_PROTOCOL_GUID {0xe5dd1403,0xd622,0xc24e, {0x84,0x88,0xc7,0x1b,0x17,0xf5,0xe8,0x02}}
#define EFI_ADAPTER_INFO_MEDIA_STATE_GUID {0xd7c74207,0xa831,0x4a26, {0xb1,0xf5,0xd1,0x93,0x06,0x5c,0xe8,0xb6}}
#define EFI_ADAPTER_INFO_NETWORK_BOOT_GUID {0x1fbd2960,0x4130,0x41e5,{0x94,0xac,0xd2,0xcf,0x03,0x7f,0xb3,0x7c}}
#define EFI_ADAPTER_INFO_SAN_MAC_ADDRESS_GUID {0x114da5ef,0x2cf1,0x4e12, {0x9b,0xbb,0xc4,0x70,0xb5,0x52,0x05,0xd9}}
#define EFI_ADAPTER_INFO_UNDI_IPV6_SUPPORT_GUID {0x4bd56be3,0x4975,0x4d8a, {0xa0,0xad,0xc4,0x91,0x20,0x4b,0x5d,0x4d}}
#define EFI_ADAPTER_INFO_MEDIA_TYPE_GUID {0x8484472f,0x71ec,0x411a, {0xb3,0x9c,0x62,0xcd,0x94,0xd9,0x91,0x6e}}
#define EFI_ADAPTER_INFO_CDAT_TYPE_GUID {0x77af24d1,0xb6f0,0x42b9, {0x83,0xf5,0x8f,0xe6,0xe8,0x3e,0xb6,0xf0}}

typedef struct _EFI_ADAPTER_INFORMATION_PROTOCOL EFI_ADAPTER_INFORMATION_PROTOCOL;

typedef struct {
	EFI_STATUS MediaState;
} EFI_ADAPTER_INFO_MEDIA_STATE;

typedef struct {
	EFI_BOOLEAN iSsciIpv4BootCapablity;
	EFI_BOOLEAN iScsiIpv6BootCapablity;
	EFI_BOOLEAN FCoeBootCapablity;
	EFI_BOOLEAN OffloadCapability;
	EFI_BOOLEAN iScsiMpioCapability;
	EFI_BOOLEAN iScsiIpv4Boot;
	EFI_BOOLEAN iScsiIpv6Boot;
	EFI_BOOLEAN FCoeBoot;
} EFI_ADAPTER_INFO_NETWORK_BOOT;

typedef struct {
	EFI_MAC_ADDRESS SanMacAddress;
} EFI_ADAPTER_INFO_SAN_MAC_ADDRESS;

typedef struct {
	EFI_BOOLEAN Ipv6Support;
} EFI_ADAPTER_INFO_UNDI_IPV6_SUPPORT;

typedef struct {
	EFI_UINT8 MediaType;
} EFI_ADAPTER_INFO_MEDIA_TYPE;

typedef struct {
	EFI_UINTN CdatSize;
	EFI_UINT8 Cdat[];
} EFI_ADAPTER_INFO_CDAT_TYPE_TYPE;

typedef
EFI_STATUS
(EFIAPI *EFI_ADAPTER_INFO_GET_INFO)(
	IN EFI_ADAPTER_INFORMATION_PROTOCOL *This,
	IN EFI_GUID *InformationType,
	OUT VOID **InformationBlock,
	OUT EFI_UINTN *InformationBlockSize
);

typedef
EFI_STATUS
(EFIAPI *EFI_ADAPTER_INFO_SET_INFO)(
	IN EFI_ADAPTER_INFORMATION_PROTOCOL *This,
	IN EFI_GUID *InformationType,
	IN VOID *InformationBlock,
	IN EFI_UINTN InformationBlockSize
);

typedef
EFI_STATUS
(EFIAPI *EFI_ADAPTER_INFO_GET_SUPPORTED_TYPES)(
	IN EFI_ADAPTER_INFORMATION_PROTOCOL *This,
	OUT EFI_GUID **InfoTypesBuffer,
	OUT EFI_UINTN *InfoTypesBufferCount
);

typedef struct _EFI_ADAPTER_INFORMATION_PROTOCOL {
	EFI_ADAPTER_INFO_GET_INFO GetInformation;
	EFI_ADAPTER_INFO_SET_INFO SetInformation;
	EFI_ADAPTER_INFO_GET_SUPPORTED_TYPES GetSupportedTypes;
} EFI_ADAPTER_INFORMATION_PROTOCOL;

#endif /* EFI_PROTOCOLS_UEFI_DRIVER_MODEL_H */
