// Auto-generated. Do not edit!

// (in-package xpkg_comm.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class xmsg_comm_data {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.id_c = null;
      this.id_t = null;
      this.id_n = null;
      this.id_f = null;
      this.len = null;
      this.data = null;
      this.time = null;
    }
    else {
      if (initObj.hasOwnProperty('id_c')) {
        this.id_c = initObj.id_c
      }
      else {
        this.id_c = 0;
      }
      if (initObj.hasOwnProperty('id_t')) {
        this.id_t = initObj.id_t
      }
      else {
        this.id_t = 0;
      }
      if (initObj.hasOwnProperty('id_n')) {
        this.id_n = initObj.id_n
      }
      else {
        this.id_n = 0;
      }
      if (initObj.hasOwnProperty('id_f')) {
        this.id_f = initObj.id_f
      }
      else {
        this.id_f = 0;
      }
      if (initObj.hasOwnProperty('len')) {
        this.len = initObj.len
      }
      else {
        this.len = 0;
      }
      if (initObj.hasOwnProperty('data')) {
        this.data = initObj.data
      }
      else {
        this.data = new Array(8).fill(0);
      }
      if (initObj.hasOwnProperty('time')) {
        this.time = initObj.time
      }
      else {
        this.time = {secs: 0, nsecs: 0};
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type xmsg_comm_data
    // Serialize message field [id_c]
    bufferOffset = _serializer.uint8(obj.id_c, buffer, bufferOffset);
    // Serialize message field [id_t]
    bufferOffset = _serializer.uint8(obj.id_t, buffer, bufferOffset);
    // Serialize message field [id_n]
    bufferOffset = _serializer.uint8(obj.id_n, buffer, bufferOffset);
    // Serialize message field [id_f]
    bufferOffset = _serializer.uint8(obj.id_f, buffer, bufferOffset);
    // Serialize message field [len]
    bufferOffset = _serializer.uint8(obj.len, buffer, bufferOffset);
    // Check that the constant length array field [data] has the right length
    if (obj.data.length !== 8) {
      throw new Error('Unable to serialize array field data - length must be 8')
    }
    // Serialize message field [data]
    bufferOffset = _arraySerializer.uint8(obj.data, buffer, bufferOffset, 8);
    // Serialize message field [time]
    bufferOffset = _serializer.time(obj.time, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type xmsg_comm_data
    let len;
    let data = new xmsg_comm_data(null);
    // Deserialize message field [id_c]
    data.id_c = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [id_t]
    data.id_t = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [id_n]
    data.id_n = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [id_f]
    data.id_f = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [len]
    data.len = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [data]
    data.data = _arrayDeserializer.uint8(buffer, bufferOffset, 8)
    // Deserialize message field [time]
    data.time = _deserializer.time(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 21;
  }

  static datatype() {
    // Returns string type for a message object
    return 'xpkg_comm/xmsg_comm_data';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9bb3169c96726b4ca470a5d97bf0777b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 id_c
    uint8 id_t
    uint8 id_n
    uint8 id_f
    uint8 len
    uint8[8] data
    time time
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new xmsg_comm_data(null);
    if (msg.id_c !== undefined) {
      resolved.id_c = msg.id_c;
    }
    else {
      resolved.id_c = 0
    }

    if (msg.id_t !== undefined) {
      resolved.id_t = msg.id_t;
    }
    else {
      resolved.id_t = 0
    }

    if (msg.id_n !== undefined) {
      resolved.id_n = msg.id_n;
    }
    else {
      resolved.id_n = 0
    }

    if (msg.id_f !== undefined) {
      resolved.id_f = msg.id_f;
    }
    else {
      resolved.id_f = 0
    }

    if (msg.len !== undefined) {
      resolved.len = msg.len;
    }
    else {
      resolved.len = 0
    }

    if (msg.data !== undefined) {
      resolved.data = msg.data;
    }
    else {
      resolved.data = new Array(8).fill(0)
    }

    if (msg.time !== undefined) {
      resolved.time = msg.time;
    }
    else {
      resolved.time = {secs: 0, nsecs: 0}
    }

    return resolved;
    }
};

module.exports = xmsg_comm_data;
