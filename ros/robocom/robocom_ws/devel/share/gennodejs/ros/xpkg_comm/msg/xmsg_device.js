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

class xmsg_device {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.dev_class = null;
      this.dev_type = null;
      this.dev_number = null;
      this.dev_enable = null;
    }
    else {
      if (initObj.hasOwnProperty('dev_class')) {
        this.dev_class = initObj.dev_class
      }
      else {
        this.dev_class = 0;
      }
      if (initObj.hasOwnProperty('dev_type')) {
        this.dev_type = initObj.dev_type
      }
      else {
        this.dev_type = 0;
      }
      if (initObj.hasOwnProperty('dev_number')) {
        this.dev_number = initObj.dev_number
      }
      else {
        this.dev_number = 0;
      }
      if (initObj.hasOwnProperty('dev_enable')) {
        this.dev_enable = initObj.dev_enable
      }
      else {
        this.dev_enable = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type xmsg_device
    // Serialize message field [dev_class]
    bufferOffset = _serializer.uint8(obj.dev_class, buffer, bufferOffset);
    // Serialize message field [dev_type]
    bufferOffset = _serializer.uint8(obj.dev_type, buffer, bufferOffset);
    // Serialize message field [dev_number]
    bufferOffset = _serializer.uint8(obj.dev_number, buffer, bufferOffset);
    // Serialize message field [dev_enable]
    bufferOffset = _serializer.uint8(obj.dev_enable, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type xmsg_device
    let len;
    let data = new xmsg_device(null);
    // Deserialize message field [dev_class]
    data.dev_class = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dev_type]
    data.dev_type = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dev_number]
    data.dev_number = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dev_enable]
    data.dev_enable = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'xpkg_comm/xmsg_device';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'fb7e43db7d28a3165b8781af2a5c7ea9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 dev_class
    uint8 dev_type
    uint8 dev_number
    uint8 dev_enable
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new xmsg_device(null);
    if (msg.dev_class !== undefined) {
      resolved.dev_class = msg.dev_class;
    }
    else {
      resolved.dev_class = 0
    }

    if (msg.dev_type !== undefined) {
      resolved.dev_type = msg.dev_type;
    }
    else {
      resolved.dev_type = 0
    }

    if (msg.dev_number !== undefined) {
      resolved.dev_number = msg.dev_number;
    }
    else {
      resolved.dev_number = 0
    }

    if (msg.dev_enable !== undefined) {
      resolved.dev_enable = msg.dev_enable;
    }
    else {
      resolved.dev_enable = 0
    }

    return resolved;
    }
};

module.exports = xmsg_device;
