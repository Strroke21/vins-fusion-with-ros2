pub mod rmw {
    #[cfg(feature = "serde")]
    use serde::{Deserialize, Serialize};

#[link(name = "vins__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__vins__msg__FeatureQuality() -> *const std::ffi::c_void;
}

#[link(name = "vins__rosidl_generator_c")]
extern "C" {
    fn vins__msg__FeatureQuality__init(msg: *mut FeatureQuality) -> bool;
    fn vins__msg__FeatureQuality__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<FeatureQuality>, size: usize) -> bool;
    fn vins__msg__FeatureQuality__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<FeatureQuality>);
    fn vins__msg__FeatureQuality__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<FeatureQuality>, out_seq: *mut rosidl_runtime_rs::Sequence<FeatureQuality>) -> bool;
}

// Corresponds to vins__msg__FeatureQuality
#[repr(C)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct FeatureQuality {
    pub header: std_msgs::msg::rmw::Header,
    pub tracked: i32,
    pub long_tracks_gt_5: i32,
    pub new_features: i32,
    pub total: i32,
    pub visual_features: i32,
    pub vx: f64,
    pub vy: f64,
    pub vz: f64,
    pub velocity_norm: f64,
    pub ba_x: f64,
    pub ba_y: f64,
    pub ba_z: f64,
    pub ba_norm: f64,
    pub bg_x: f64,
    pub bg_y: f64,
    pub bg_z: f64,
    pub bg_norm: f64,
}



impl Default for FeatureQuality {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !vins__msg__FeatureQuality__init(&mut msg as *mut _) {
        panic!("Call to vins__msg__FeatureQuality__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for FeatureQuality {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vins__msg__FeatureQuality__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vins__msg__FeatureQuality__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vins__msg__FeatureQuality__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for FeatureQuality {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for FeatureQuality where Self: Sized {
  const TYPE_NAME: &'static str = "vins/msg/FeatureQuality";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__vins__msg__FeatureQuality() }
  }
}


}  // mod rmw

#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct FeatureQuality {
    pub header: std_msgs::msg::Header,
    pub tracked: i32,
    pub long_tracks_gt_5: i32,
    pub new_features: i32,
    pub total: i32,
    pub visual_features: i32,
    pub vx: f64,
    pub vy: f64,
    pub vz: f64,
    pub velocity_norm: f64,
    pub ba_x: f64,
    pub ba_y: f64,
    pub ba_z: f64,
    pub ba_norm: f64,
    pub bg_x: f64,
    pub bg_y: f64,
    pub bg_z: f64,
    pub bg_norm: f64,
}



impl Default for FeatureQuality {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(crate::msg::rmw::FeatureQuality::default())
  }
}

impl rosidl_runtime_rs::Message for FeatureQuality {
  type RmwMsg = crate::msg::rmw::FeatureQuality;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        tracked: msg.tracked,
        long_tracks_gt_5: msg.long_tracks_gt_5,
        new_features: msg.new_features,
        total: msg.total,
        visual_features: msg.visual_features,
        vx: msg.vx,
        vy: msg.vy,
        vz: msg.vz,
        velocity_norm: msg.velocity_norm,
        ba_x: msg.ba_x,
        ba_y: msg.ba_y,
        ba_z: msg.ba_z,
        ba_norm: msg.ba_norm,
        bg_x: msg.bg_x,
        bg_y: msg.bg_y,
        bg_z: msg.bg_z,
        bg_norm: msg.bg_norm,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      tracked: msg.tracked,
      long_tracks_gt_5: msg.long_tracks_gt_5,
      new_features: msg.new_features,
      total: msg.total,
      visual_features: msg.visual_features,
      vx: msg.vx,
      vy: msg.vy,
      vz: msg.vz,
      velocity_norm: msg.velocity_norm,
      ba_x: msg.ba_x,
      ba_y: msg.ba_y,
      ba_z: msg.ba_z,
      ba_norm: msg.ba_norm,
      bg_x: msg.bg_x,
      bg_y: msg.bg_y,
      bg_z: msg.bg_z,
      bg_norm: msg.bg_norm,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      tracked: msg.tracked,
      long_tracks_gt_5: msg.long_tracks_gt_5,
      new_features: msg.new_features,
      total: msg.total,
      visual_features: msg.visual_features,
      vx: msg.vx,
      vy: msg.vy,
      vz: msg.vz,
      velocity_norm: msg.velocity_norm,
      ba_x: msg.ba_x,
      ba_y: msg.ba_y,
      ba_z: msg.ba_z,
      ba_norm: msg.ba_norm,
      bg_x: msg.bg_x,
      bg_y: msg.bg_y,
      bg_z: msg.bg_z,
      bg_norm: msg.bg_norm,
    }
  }
}


