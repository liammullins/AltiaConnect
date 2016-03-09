#include "altiaupnpcontroller.h"


/** Copy of Controller for static files */
extern StaticFileController* staticFileController;

AltiaUPnPController::AltiaUPnPController(QObject* parent)
    : HttpRequestHandler(parent)
{
    //StaticFileController = this;
}

void AltiaUPnPController::service(HttpRequest &request, HttpResponse &response)
{

    QByteArray path = request.getPath();
    qDebug("RequestMapper: path = %s",path.data());

    try
    {
        // For the following paths, each request gets its own new instance of the related controller
        staticFileController->service(request, response);
    }
    catch(...)
    {
        qDebug("RequestMapper: file controller issue");
    }

    qDebug("RequestMapper: finished request");

}
