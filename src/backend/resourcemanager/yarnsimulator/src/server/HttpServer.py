import os
import sys
import web
import logging

class WebCluster:
    def __init__(self):
        pass

    def GET(self, name = None):
        return """
<html>
    <head>
        <title>YarnSimulator</title>
    </head>
    <body>
        Hi all,<br><br>
        It will be done next week!<br><br><br>
        Regards,<br>
        Ivan<br>
    </body>

</html>"""


urls = (
    '/' ,   'WebCluster',        
)

class HttpService:
    def __init__(self, port, cluster, resource_tracker):
        self.port = port
        self.cluster = cluster
        self.tracker = resource_tracker

    def run(self):
        app = web.application(urls, globals())
        sys.argc = 2
        sys.argv = sys.argv[0:2]
        sys.argv[1] = '%s' % self.port
        
        app.run()

if __name__ == '__main__':
    server = HttpService(18081, None, None)
    server.run()
