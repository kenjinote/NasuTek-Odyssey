
 @ stdcall ArcFilterDprIndicateReceive(ptr ptr ptr long)
 @ stdcall ArcFilterDprIndicateReceiveComplete(ptr)
 @ stdcall EthFilterDprIndicateReceive(ptr ptr ptr ptr long ptr long long)
 @ stdcall EthFilterDprIndicateReceiveComplete(ptr)
 @ stdcall FddiFilterDprIndicateReceive(ptr ptr ptr long ptr long ptr long long)
 @ stdcall FddiFilterDprIndicateReceiveComplete(ptr)
 @ stdcall NDIS_BUFFER_TO_SPAN_PAGES(ptr)
 @ stdcall NdisAcquireReadWriteLock(ptr long ptr)
 @ stdcall NdisAcquireSpinLock(ptr)
 @ stdcall NdisAdjustBufferLength(ptr long)
 @ stdcall NdisAllocateBuffer(ptr ptr ptr ptr long)
 @ stdcall NdisAllocateBufferPool(ptr ptr long)
 @ stdcall NdisAllocateDmaChannel(ptr ptr ptr ptr long)
 @ stdcall NdisAllocateMemory(ptr long long double)
 @ stdcall NdisAllocateFromBlockPool(ptr)
 @ stdcall NdisAllocateMemoryWithTag(ptr long long)
 @ stdcall NdisAllocatePacket(ptr ptr ptr)
 @ stdcall NdisAllocatePacketPool(ptr ptr long long)
 @ stdcall NdisAllocatePacketPoolEx(ptr ptr long long long)
 @ stdcall NdisAllocateSharedMemory(ptr long long ptr ptr)
 @ stdcall NdisAllocateSpinLock(ptr)
 @ stdcall NdisAnsiStringToUnicodeString(ptr ptr)
 @ stdcall NdisBufferLength(ptr)
 @ stdcall NdisBufferVirtualAddress(ptr)
 @ stdcall NdisCancelSendPackets(ptr ptr)
 @ stdcall NdisCancelTimer(ptr ptr)
 @ stdcall NdisClAddParty(ptr ptr ptr ptr)
 @ stdcall NdisClCloseAddressFamily(ptr)
 @ stdcall NdisClCloseCall(ptr ptr ptr long)
 @ stdcall NdisClDeregisterSap(ptr)
 @ stdcall NdisClDropParty(ptr ptr long)
 @ stdcall NdisClGetProtocolVcContextFromTapiCallId(double ptr)
 @ stdcall NdisClIncomingCallComplete(long ptr ptr)
 @ stdcall NdisClMakeCall(ptr ptr ptr ptr)
 @ stdcall NdisClModifyCallQoS(ptr ptr)
 @ stdcall NdisClOpenAddressFamily(ptr ptr ptr ptr long ptr)
 @ stdcall NdisClRegisterSap(ptr ptr ptr ptr)
 @ stdcall NdisCloseAdapter(ptr ptr)
 @ stdcall NdisCloseConfiguration(ptr)
 @ stdcall NdisCloseFile(ptr)
 @ stdcall NdisCmActivateVc(ptr ptr)
 @ stdcall NdisCmAddPartyComplete(long ptr ptr ptr)
 @ stdcall NdisCmCloseAddressFamilyComplete(long ptr)
 @ stdcall NdisCmCloseCallComplete(long ptr ptr)
 @ stdcall NdisCmDeactivateVc(ptr)
 @ stdcall NdisCmDeregisterSapComplete(long ptr)
 @ stdcall NdisCmDispatchCallConnected(ptr)
 @ stdcall NdisCmDispatchIncomingCall(ptr ptr ptr)
 @ stdcall NdisCmDispatchIncomingCallQoSChange(ptr ptr)
 @ stdcall NdisCmDispatchIncomingCloseCall(long ptr ptr long)
 @ stdcall NdisCmDispatchIncomingDropParty(ptr ptr ptr long)
 @ stdcall NdisCmDropPartyComplete(long ptr)
 @ stdcall NdisCmMakeCallComplete(long ptr ptr ptr ptr)
 @ stdcall NdisCmModifyCallQoSComplete(long ptr ptr)
 @ stdcall NdisCmOpenAddressFamilyComplete(long ptr ptr)
 @ stdcall NdisCmRegisterAddressFamily(ptr ptr ptr long)
 @ stdcall NdisCmRegisterSapComplete(long ptr ptr)
 @ stdcall NdisCoAssignInstanceName(ptr ptr ptr)
 @ stdcall NdisCoCreateVc(ptr ptr ptr ptr)
 @ stdcall NdisCoDeleteVc(ptr)
 @ stdcall NdisCoGetTapiCallId(ptr ptr)
 @ stdcall NdisCoRequest(ptr ptr ptr ptr ptr)
 @ stdcall NdisCoRequestComplete(long ptr ptr ptr ptr)
 @ stdcall NdisCoSendPackets(ptr ptr long)
 @ stdcall NdisCompareAnsiString(ptr ptr long)
 @ stdcall NdisCompareUnicodeString(ptr ptr long)
 @ stdcall NdisCompleteBindAdapter(ptr long long)
 @ stdcall NdisCompleteCloseAdapter(ptr long)
 @ stdcall NdisCompleteDmaTransfer(ptr ptr ptr long long long)
 @ stdcall NdisCompleteOpenAdapter(ptr long long)
 @ stdcall NdisCompletePnPEvent(long ptr ptr)
 @ stdcall NdisCompleteQueryStatistics(ptr ptr long)
 @ stdcall NdisCompleteUnbindAdapter(ptr long)
 @ stdcall NdisConvertStringToAtmAddress(ptr ptr ptr)
 @ stdcall NdisCopyBuffer(ptr ptr ptr ptr long long)
 @ stdcall NdisCopyFromPacketToPacket(ptr long long ptr long ptr)
 @ stdcall NdisCopyFromPacketToPacketSafe(ptr long long ptr long ptr long)
 @ stdcall NdisCreateBlockPool(long long long ptr)
 @ stdcall NdisDeregisterAdapter(ptr)
 @ stdcall NdisDeregisterAdapterShutdownHandler(ptr)
 @ stdcall NdisDeregisterMac(ptr ptr)
 @ stdcall NdisDeregisterProtocol(ptr ptr)
 @ stdcall NdisDeregisterTdiCallBack()
 @ stdcall NdisDestroyBlockPool(ptr)
 @ stdcall NdisDprAcquireSpinLock(ptr)
 @ stdcall NdisDprAllocatePacket(ptr ptr ptr)
 @ stdcall NdisDprAllocatePacketNonInterlocked(ptr ptr ptr)
 @ stdcall NdisDprFreePacket(ptr)
 @ stdcall NdisDprFreePacketNonInterlocked(ptr)
 @ stdcall NdisDprReleaseSpinLock(ptr)
 @ stdcall NdisEqualString(ptr ptr long)
 @ stdcall NdisFreeBuffer(ptr)
 @ stdcall NdisFreeBufferPool(ptr)
 @ stdcall NdisFreeDmaChannel(ptr)
 @ stdcall NdisFreeToBlockPool(ptr)
 @ stdcall NdisFreeMemory(ptr long long)
 @ stdcall NdisFreePacket(ptr)
 @ stdcall NdisFreePacketPool(ptr)
 @ stdcall NdisFreeSharedMemory(ptr long long ptr double)
 @ stdcall NdisFreeSpinLock(ptr)
 @ stdcall NdisGeneratePartialCancelId()
 @ stdcall NdisGetBufferPhysicalArraySize(ptr ptr)
 @ stdcall NdisGetCurrentProcessorCounts(ptr ptr ptr)
 @ stdcall NdisGetCurrentProcessorCpuUsage(ptr)
 @ stdcall NdisGetCurrentSystemTime(ptr)
 @ stdcall NdisGetDriverHandle(ptr ptr)
 @ stdcall NdisGetFirstBufferFromPacket(ptr ptr ptr ptr ptr)
 @ stdcall NdisGetFirstBufferFromPacketSafe(ptr ptr ptr ptr ptr long)
 @ stdcall NdisGetPacketCancelId(ptr)
 @ stdcall NdisGetPoolFromPacket(ptr)
 @ stdcall NdisGetReceivedPacket(ptr ptr)
 @ stdcall NdisGetRoutineAddress(ptr)
 @ stdcall NdisGetSharedDataAlignment()
 @ stdcall NdisGetSystemUpTime(ptr)
 @ stdcall NdisGetVersion()
 @ stdcall NdisIMAssociateMiniport(ptr ptr)
 @ stdcall NdisIMCancelInitializeDeviceInstance(ptr ptr)
 @ stdcall NdisIMCopySendCompletePerPacketInfo(ptr ptr)
 @ stdcall NdisIMCopySendPerPacketInfo(ptr ptr)
 @ stdcall NdisIMDeInitializeDeviceInstance(ptr)
 @ stdcall NdisIMDeregisterLayeredMiniport(ptr)
 @ stdcall NdisIMGetBindingContext(ptr)
 @ stdcall NdisIMGetCurrentPacketStack(ptr ptr)
 @ stdcall NdisIMGetDeviceContext(ptr)
 @ stdcall NdisIMInitializeDeviceInstance(ptr ptr)
 @ stdcall NdisIMInitializeDeviceInstanceEx(ptr ptr ptr)
 @ stdcall NdisIMNotifyPnPEvent(ptr ptr)
 @ stdcall NdisImmediateReadPciSlotInformation(ptr long long ptr long)
 @ stdcall NdisImmediateReadPortUchar(ptr long ptr)
 @ stdcall NdisImmediateReadPortUlong(ptr long ptr)
 @ stdcall NdisImmediateReadPortUshort(ptr long ptr)
 @ stdcall NdisImmediateReadSharedMemory(ptr long ptr long)
 @ stdcall NdisImmediateWritePciSlotInformation(ptr long long ptr long)
 @ stdcall NdisImmediateWritePortUchar(ptr long long)
 @ stdcall NdisImmediateWritePortUlong(ptr long long)
 @ stdcall NdisImmediateWritePortUshort(ptr long long)
 @ stdcall NdisImmediateWriteSharedMemory(ptr long ptr long)
 @ stdcall NdisIMQueueMiniportCallback(ptr ptr ptr)
 @ stdcall NdisIMRegisterLayeredMiniport(ptr ptr long ptr)
 @ stdcall NdisIMRevertBack(ptr ptr)
 @ stdcall NdisIMSwitchToMiniport(ptr ptr)
 @ stdcall NdisInitAnsiString(ptr ptr)
 @ stdcall NdisInitializeEvent(ptr)
 @ stdcall NdisInitializeReadWriteLock(ptr)
 @ stdcall NdisInitializeString(ptr ptr)
 @ stdcall NdisInitializeTimer(ptr ptr ptr)
 @ stdcall NdisInitializeWrapper(ptr ptr ptr ptr)
 @ stdcall NdisInitUnicodeString(ptr ptr)
 @ stdcall NdisInterlockedAddLargeInteger(ptr double ptr)
 @ stdcall NdisInterlockedAddUlong(ptr long ptr)
 @ stdcall NdisInterlockedDecrement(ptr)
 @ stdcall NdisInterlockedIncrement(ptr)
 @ stdcall NdisInterlockedInsertHeadList(ptr ptr ptr)
 @ stdcall NdisInterlockedInsertTailList(ptr ptr ptr)
 @ stdcall NdisInterlockedPopEntrySList(ptr ptr)
 @ stdcall NdisInterlockedPushEntrySList(ptr ptr ptr)
 @ stdcall NdisInterlockedRemoveHeadList(ptr ptr)
 @ stdcall NdisMAllocateMapRegisters(ptr long long long long)
 @ stdcall NdisMAllocateSharedMemory(ptr long long ptr ptr)
 @ stdcall NdisMAllocateSharedMemoryAsync(ptr long long ptr)
 @ stdcall NdisMapFile(ptr ptr ptr)
 @ stdcall NdisMapIoSpace(ptr ptr ptr double long)
# @ stdcall NdisMatchPdoWithPacket ?
 @ stdcall NdisMCancelTimer(ptr ptr)
 @ stdcall NdisMCloseLog(ptr)
 @ stdcall NdisMCmActivateVc(ptr ptr)
 @ stdcall NdisMCmCreateVc(ptr ptr ptr ptr)
 @ stdcall NdisMCmDeactivateVc(ptr)
 @ stdcall NdisMCmDeleteVc(ptr)
 @ stdcall NdisMCmRegisterAddressFamily(ptr ptr ptr long)
 @ stdcall NdisMCmRequest(ptr ptr ptr ptr)
 @ stdcall NdisMCoActivateVcComplete(long ptr ptr)
 @ stdcall NdisMCoDeactivateVcComplete(long ptr)
 @ stdcall NdisMCoIndicateReceivePacket(ptr ptr long)
 @ stdcall NdisMCoIndicateStatus(ptr ptr long ptr long)
 @ stdcall NdisMCompleteBufferPhysicalMapping(ptr ptr long)
 @ stdcall NdisMCoReceiveComplete(ptr)
 @ stdcall NdisMCoRequestComplete(long ptr ptr)
 @ stdcall NdisMCoSendComplete(ptr ptr ptr)
 @ stdcall NdisMCreateLog(ptr long ptr)
 @ stdcall NdisMDeregisterAdapterShutdownHandler(ptr)
 @ stdcall NdisMDeregisterDevice(ptr)
 @ stdcall NdisMDeregisterDmaChannel(ptr)
 @ stdcall NdisMDeregisterInterrupt(ptr)
 @ stdcall NdisMDeregisterIoPortRange(ptr long long ptr)
 @ stdcall NdisMFlushLog(ptr)
 @ stdcall NdisMFreeMapRegisters(ptr)
 @ stdcall NdisMFreeSharedMemory(ptr long long ptr double)
 @ stdcall NdisMGetDeviceProperty(ptr ptr ptr ptr ptr ptr)
 @ stdcall NdisMGetDmaAlignment(ptr)
 @ stdcall NdisMIndicateStatus(ptr long ptr long)
 @ stdcall NdisMIndicateStatusComplete(ptr)
 @ stdcall NdisMInitializeScatterGatherDma(ptr long long)
 @ stdcall NdisMInitializeTimer(ptr ptr ptr ptr)
 @ stdcall NdisMMapIoSpace(ptr ptr double long)
 @ stdcall NdisMPciAssignResources(ptr long ptr)
 @ stdcall NdisMPromoteMiniport(ptr)
 @ stdcall NdisMQueryAdapterInstanceName(ptr ptr)
 @ stdcall NdisMQueryAdapterResources(ptr ptr ptr ptr)
 @ stdcall NdisMQueryInformationComplete(ptr long)
 @ stdcall NdisMReadDmaCounter(ptr)
 @ stdcall NdisMRegisterAdapterShutdownHandler(ptr ptr ptr)
 @ stdcall NdisMRegisterDevice(ptr ptr ptr ptr ptr ptr)
 @ stdcall NdisMRegisterDmaChannel(ptr ptr long long ptr long)
 @ stdcall NdisMRegisterInterrupt(ptr ptr long long long long long)
 @ stdcall NdisMRegisterIoPortRange(ptr ptr long long)
 @ stdcall NdisMRegisterMiniport(ptr ptr long)
 @ stdcall NdisMRegisterUnloadHandler(ptr ptr)
 @ stdcall NdisMRemoveMiniport(ptr)
 @ stdcall NdisMResetComplete(ptr long long)
 @ stdcall NdisMSendComplete(ptr ptr long)
 @ stdcall NdisMSendResourcesAvailable(ptr)
 @ stdcall NdisMSetAttributes(ptr ptr long long)
 @ stdcall NdisMSetAttributesEx(ptr ptr long long long)
 @ stdcall NdisMSetInformationComplete(ptr long)
 @ stdcall NdisMSetMiniportSecondary(ptr ptr)
 @ stdcall NdisMSetPeriodicTimer(ptr long)
 @ stdcall NdisMSetTimer(ptr long)
 @ stdcall NdisMSleep(long)
 @ stdcall NdisMStartBufferPhysicalMapping(ptr ptr long long ptr ptr)
 @ stdcall NdisMSynchronizeWithInterrupt(ptr ptr ptr)
 @ stdcall NdisMTransferDataComplete(ptr ptr long long)
 @ stdcall NdisMUnmapIoSpace(ptr ptr long)
 @ stdcall NdisMWanIndicateReceive(ptr ptr ptr ptr long)
 @ stdcall NdisMWanIndicateReceiveComplete(ptr)
 @ stdcall NdisMWanSendComplete(ptr ptr long)
 @ stdcall NdisMWriteLogData(ptr ptr long)
 @ stdcall NdisOpenAdapter(ptr ptr ptr ptr ptr long ptr ptr ptr long ptr)
 @ stdcall NdisOpenConfiguration(ptr ptr ptr)
 @ stdcall NdisOpenConfigurationKeyByIndex(ptr ptr long ptr ptr)
 @ stdcall NdisOpenConfigurationKeyByName(ptr ptr ptr ptr)
 @ stdcall NdisOpenFile(ptr ptr ptr ptr double)
 @ stdcall NdisOpenProtocolConfiguration(ptr ptr ptr)
 @ stdcall NdisOverrideBusNumber(ptr ptr long)
 @ stdcall NdisPacketPoolUsage(ptr)
 @ stdcall NdisPacketSize(long)
 @ stdcall NdisPciAssignResources(ptr ptr ptr long ptr)
 @ stdcall NdisQueryAdapterInstanceName(ptr ptr)
 @ stdcall NdisQueryBindInstanceName(ptr ptr)
 @ stdcall NdisQueryBuffer(ptr ptr ptr)
 @ stdcall NdisQueryBufferOffset(ptr ptr ptr)
 @ stdcall NdisQueryBufferSafe(ptr ptr ptr long)
 @ stdcall NdisQueryMapRegisterCount(long ptr)
 @ stdcall NdisQueryPendingIOCount(ptr ptr)
 @ stdcall NdisReadConfiguration(ptr ptr ptr ptr long)
 @ stdcall NdisReadEisaSlotInformation(ptr ptr ptr ptr)
 @ stdcall NdisReadEisaSlotInformationEx(ptr ptr ptr ptr ptr)
 @ stdcall NdisReadMcaPosInformation(ptr ptr ptr ptr)
 @ stdcall NdisReadNetworkAddress(ptr ptr ptr ptr)
 @ stdcall NdisReadPciSlotInformation(ptr long long ptr long)
 @ stdcall NdisReadPcmciaAttributeMemory(ptr long ptr long)
 @ stdcall NdisReEnumerateProtocolBindings(ptr)
 @ stdcall NdisRegisterAdapter(ptr ptr ptr ptr ptr ptr)
 @ stdcall NdisRegisterAdapterShutdownHandler(ptr ptr ptr)
 @ stdcall NdisRegisterProtocol(ptr ptr ptr long)
 @ stdcall NdisRegisterTdiCallBack(ptr ptr)
 @ stdcall NdisReleaseAdapterResources(ptr)
 @ stdcall NdisReleaseReadWriteLock(ptr ptr)
 @ stdcall NdisReleaseSpinLock(ptr)
 @ stdcall NdisRequest(ptr ptr ptr)
 @ stdcall NdisReset(ptr ptr)
 @ stdcall NdisResetEvent(ptr)
 @ stdcall NdisReturnPackets(ptr long)
 @ stdcall NdisSend(ptr ptr ptr)
 @ stdcall NdisSendPackets(ptr ptr long)
 @ stdcall NdisSetEvent(ptr)
 @ stdcall NdisSetPacketCancelId(ptr ptr)
 @ stdcall NdisSetPacketPoolProtocolId(ptr long)
 @ stdcall NdisSetPacketStatus(ptr long ptr long)
 @ stdcall NdisSetProtocolFilter(ptr ptr ptr ptr long long long ptr)
 @ stdcall NdisSetTimer(ptr long)
 @ stdcall NdisSetTimerEx(ptr long ptr)
 @ stdcall NdisSetupDmaTransfer(ptr ptr ptr long long long)
 @ stdcall NdisSystemProcessorCount()
 @ stdcall NdisTerminateWrapper(ptr ptr)
 @ stdcall NdisTransferData(ptr ptr ptr long long ptr ptr)
 @ stdcall NdisUnchainBufferAtBack(ptr ptr)
 @ stdcall NdisUnchainBufferAtFront(ptr ptr)
 @ stdcall NdisUnicodeStringToAnsiString(ptr ptr)
 @ stdcall NdisUnmapFile(ptr)
 @ stdcall NdisUpcaseUnicodeString(ptr ptr)
 @ stdcall NdisUpdateSharedMemory(ptr long ptr double)
 @ stdcall NdisWaitEvent(ptr long)
 @ stdcall NdisWriteConfiguration(ptr ptr ptr ptr)
 @ cdecl NdisWriteErrorLogEntry(ptr long long)
 @ stdcall NdisWriteEventLogEntry(ptr long long long ptr long ptr)
 @ stdcall NdisWritePciSlotInformation(ptr long long ptr long)
 @ stdcall NdisWritePcmciaAttributeMemory(ptr long ptr long)
 @ stdcall TrFilterDprIndicateReceive(ptr ptr ptr long ptr long long)
 @ stdcall TrFilterDprIndicateReceiveComplete(ptr)
 @ stdcall NdisScheduleWorkItem(ptr)