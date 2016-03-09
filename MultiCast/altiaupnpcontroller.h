#ifndef ALTIAUPNPCONTROLLER_H
#define ALTIAUPNPCONTROLLER_H

#include "project_includes.h"


class AltiaUPnPController : public HttpRequestHandler
{

public:

    AltiaUPnPController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);


};

#endif // ALTIAUPNPCONTROLLER_H
