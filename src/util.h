#pragma once

#include <libvirt/libvirt.h>
#include <stdlib.h>
#include <systemd/sd-bus.h>
#include <unistd.h>

#define _cleanup_(_x) __attribute__((__cleanup__(_x)))

int
virtDBusUtilMessageAppendTypedParameters(sd_bus_message *message,
                                         virTypedParameterPtr parameters,
                                         int n_parameters);

int
virtDBusUtilSetLastVirtError(sd_bus_error *error);

char *
virtDBusUtilBusPathForVirDomain(virDomainPtr domain);

virDomainPtr
virtDBusUtilVirDomainFromBusPath(virConnectPtr connection,
                                 const char *path);

static inline void
virtDBusUtilFreep(void *p)
{
        free(*(void **)p);
}

static inline void
virtDBusUtilClosep(int *fdp)
{
    if (*fdp >= 0)
        close(*fdp);
}

static inline void
virtDBusUtilStrvFreep(void *p)
{
    char **strv = *(char ***)p;

    if (strv == NULL)
        return;

    for (unsigned i = 0; strv[i] != NULL; i += 1)
        free(strv[i]);

    free(strv);
}

static inline void
virtDBusUtilVirDomainFreep(virDomainPtr *domainp)
{
    if (*domainp)
        virDomainFree(*domainp);
}

static inline void
virtDBusUtilVirDomainListFreep(virDomainPtr **domainsp)
{
    virDomainPtr *domains = *domainsp;

    if (!domains)
        return;

    for (int i = 0; domains[i] != NULL; i += 1)
        virDomainFree(domains[i]);

    free(domains);
}
