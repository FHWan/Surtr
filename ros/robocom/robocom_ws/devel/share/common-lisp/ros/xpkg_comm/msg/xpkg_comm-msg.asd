
(cl:in-package :asdf)

(defsystem "xpkg_comm-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "xmsg_comm_data" :depends-on ("_package_xmsg_comm_data"))
    (:file "_package_xmsg_comm_data" :depends-on ("_package"))
    (:file "xmsg_device" :depends-on ("_package_xmsg_device"))
    (:file "_package_xmsg_device" :depends-on ("_package"))
    (:file "xmsg_device_list" :depends-on ("_package_xmsg_device_list"))
    (:file "_package_xmsg_device_list" :depends-on ("_package"))
  ))