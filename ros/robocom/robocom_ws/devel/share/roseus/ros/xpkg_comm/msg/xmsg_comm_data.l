;; Auto-generated. Do not edit!


(when (boundp 'xpkg_comm::xmsg_comm_data)
  (if (not (find-package "XPKG_COMM"))
    (make-package "XPKG_COMM"))
  (shadow 'xmsg_comm_data (find-package "XPKG_COMM")))
(unless (find-package "XPKG_COMM::XMSG_COMM_DATA")
  (make-package "XPKG_COMM::XMSG_COMM_DATA"))

(in-package "ROS")
;;//! \htmlinclude xmsg_comm_data.msg.html


(defclass xpkg_comm::xmsg_comm_data
  :super ros::object
  :slots (_id_c _id_t _id_n _id_f _len _data _time ))

(defmethod xpkg_comm::xmsg_comm_data
  (:init
   (&key
    ((:id_c __id_c) 0)
    ((:id_t __id_t) 0)
    ((:id_n __id_n) 0)
    ((:id_f __id_f) 0)
    ((:len __len) 0)
    ((:data __data) (make-array 8 :initial-element 0 :element-type :char))
    ((:time __time) (instance ros::time :init))
    )
   (send-super :init)
   (setq _id_c (round __id_c))
   (setq _id_t (round __id_t))
   (setq _id_n (round __id_n))
   (setq _id_f (round __id_f))
   (setq _len (round __len))
   (setq _data __data)
   (setq _time __time)
   self)
  (:id_c
   (&optional __id_c)
   (if __id_c (setq _id_c __id_c)) _id_c)
  (:id_t
   (&optional __id_t)
   (if __id_t (setq _id_t __id_t)) _id_t)
  (:id_n
   (&optional __id_n)
   (if __id_n (setq _id_n __id_n)) _id_n)
  (:id_f
   (&optional __id_f)
   (if __id_f (setq _id_f __id_f)) _id_f)
  (:len
   (&optional __len)
   (if __len (setq _len __len)) _len)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:time
   (&optional __time)
   (if __time (setq _time __time)) _time)
  (:serialization-length
   ()
   (+
    ;; uint8 _id_c
    1
    ;; uint8 _id_t
    1
    ;; uint8 _id_n
    1
    ;; uint8 _id_f
    1
    ;; uint8 _len
    1
    ;; uint8[8] _data
    (* 1    8)
    ;; time _time
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _id_c
       (write-byte _id_c s)
     ;; uint8 _id_t
       (write-byte _id_t s)
     ;; uint8 _id_n
       (write-byte _id_n s)
     ;; uint8 _id_f
       (write-byte _id_f s)
     ;; uint8 _len
       (write-byte _len s)
     ;; uint8[8] _data
     (princ _data s)
     ;; time _time
       (write-long (send _time :sec) s) (write-long (send _time :nsec) s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _id_c
     (setq _id_c (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _id_t
     (setq _id_t (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _id_n
     (setq _id_n (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _id_f
     (setq _id_f (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _len
     (setq _len (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8[8] _data
   (setq _data (make-array 8 :element-type :char))
   (replace _data buf :start2 ptr-) (incf ptr- 8)
   ;; time _time
     (send _time :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _time :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get xpkg_comm::xmsg_comm_data :md5sum-) "9bb3169c96726b4ca470a5d97bf0777b")
(setf (get xpkg_comm::xmsg_comm_data :datatype-) "xpkg_comm/xmsg_comm_data")
(setf (get xpkg_comm::xmsg_comm_data :definition-)
      "uint8 id_c
uint8 id_t
uint8 id_n
uint8 id_f
uint8 len
uint8[8] data
time time

")



(provide :xpkg_comm/xmsg_comm_data "9bb3169c96726b4ca470a5d97bf0777b")


