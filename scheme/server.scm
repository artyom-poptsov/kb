#!/usr/bin/env -S guile -e main
!#

(use-modules (gnutls))

;; Server-side.

(define %addr INADDR_LOOPBACK)
(define %port 8082)

(define (handle-client client)
  (let ((server (make-session connection-end/server)))
    (set-session-default-priority! server)

    ;; Request the "anonymous Diffie-Hellman" key exchange method.
    (set-session-priorities! server "NORMAL:+ANON-DH")

    ;; Specify the underlying transport socket.
    (set-session-transport-fd! server (fileno (car client)))

    ;; Create anonymous credentials.
    (let ((cred (make-anonymous-server-credentials))
          (dh-params (make-dh-parameters 1024)))
      ;; Note: DH parameter generation can take some time.
      (set-anonymous-server-dh-parameters! cred dh-params)
      (set-session-credentials! server cred))

    ;; Perform the TLS handshake with the client.
    (handshake server)

    ;; Receive data over the TLS record layer.
    (let ((message (read (session-record-port server))))
      (format #t "received the following message: ~a~%"
              message)

      (bye server close-request/rdwr))))

(define (main args)
  (let ((s (socket PF_INET SOCK_STREAM 0)))
    (bind s AF_INET %addr %port)
    (listen s 1)
    (while #t
      (let ((client (accept s)))
            (handle-client client)))))
