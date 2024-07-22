#!/usr/bin/env -S guile -e main
!#

(use-modules (gnutls))

(define %addr INADDR_LOOPBACK)
(define %port 8082)

;; Client-side.

(define (main args)
  (let ((s (socket PF_INET SOCK_STREAM 0)))
    (connect s
             AF_INET
             %addr
             %port)

    (let ((client (make-session connection-end/client)))
      ;; Use the default settings.
      (set-session-default-priority! client)

      ;; Request the "anonymous Diffie-Hellman" key exchange method.
      (set-session-priorities! client "NORMAL:+ANON-DH")

      ;; Specify the underlying socket.
      (set-session-transport-fd! client (fileno s))

      ;; Create anonymous credentials.
      (set-session-credentials! client
                                (make-anonymous-client-credentials))

      ;; Perform the TLS handshake with the server.
      (handshake client)

      ;; Send data over the TLS record layer.
      (write "hello, world!" (session-record-port client))

      ;; Terminate the TLS session.
      (bye client close-request/rdwr))))

