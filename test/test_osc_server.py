import argparse

from pythonosc import dispatcher
from pythonosc import osc_server


def handler(address, *args):
    print("MESSAGE ", address)
    for arg in args:
        print('\t', arg)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--ip",
                        default="127.0.0.1", help="The ip to listen on")
    parser.add_argument("--port",
                        type=int, default=7110, help="The port to listen on")
    args = parser.parse_args()

    dispatcher = dispatcher.Dispatcher()

    dispatcher.map("*", handler)
    # dispatcher.map("/new_user", handler)
    # dispatcher.map("/lost_user", handler)

    server = osc_server.ThreadingOSCUDPServer(
        (args.ip, args.port), dispatcher)
    print("Serving on {}".format(server.server_address))
    server.serve_forever()
