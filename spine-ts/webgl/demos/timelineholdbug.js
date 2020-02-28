var timeLineHoldBug = function(canvas, bgColor) {
	var assetManager;

	var DEMO_NAME = "TimeLineHold Bug Demo";

	function init () {
		assetManager = spineDemos.assetManager;
		assetManager.loadJson(DEMO_NAME, "TimeLineHoldBug.json");
	}

	function loadingComplete () {
		startTest(loadSkeleton("Skeleton"));
	}

	function startTest (skeletonObjects) {
		var skeleton = skeletonObjects.skeleton,
			animationState = skeletonObjects.state,
			trackEntry,
			t;

		animationState.setEmptyAnimation(0, 0)

		trackEntry = animationState.addAnimation(0, 'scale_3', false, 0)
		trackEntry.mixDuration = 300;
		trackEntry.listener = {
			end: function() {
				console.log(t, 'Ending the hold animation (scale_3)');
			}
		};

		for (t = 0; t < 100; t++) {
			update(skeleton, animationState, 1);
		}

		trackEntry = animationState.addAnimation(0, 'scale_2', false, 0);

		trackEntry.mixDuration = 100;
		trackEntry.listener = {
			complete: function() {
				console.log(t, 'Complete scale_2');
			}
		};

		for (;t < 700; t++) {
			update(skeleton, animationState, 1);
		}
		
		console.log('After 200 seconds, "scale_2" is fully mixed in, however, "scale_3" remains on the track untill it is fully mixed in as well (after 300 seconds)');
		console.log('This seems to be an issue with "AnimationState.HOLD" since the behavior is different if "scale_3" would use a different timeline');
	}

	function update (skeleton, animationState, dt) {
		animationState.update(dt);
		animationState.apply(skeleton);
		skeleton.updateWorldTransform();
	}

	function loadSkeleton(name, animation, sequenceSlots) {
		var attachmentLoader = {
			'newRegionAttachment': function() {},
			'newBoundingBoxAttachment': function() {},
			'newMeshAttachment': function() {},
			'newPathAttachment': function() {},
			'newPointAttachment': function() {},
			'newClippingAttachment': function() {}
		};

		var skeletonJson = new spine.SkeletonJson(attachmentLoader);
		var skeletonData = assetManager.get(DEMO_NAME, "TimeLineHoldBug.json");
		var spineSkeletonData = skeletonJson.readSkeletonData(skeletonData);
		var skeleton = new spine.Skeleton(spineSkeletonData);
		var state = new spine.AnimationState(new spine.AnimationStateData(spineSkeletonData));

		return {
			skeleton: skeleton,
			state: state,
		};
	}

	function render () {
	}

	timeLineHoldBug.loadingComplete = loadingComplete;
	timeLineHoldBug.render = render;
	timeLineHoldBug.DEMO_NAME = DEMO_NAME;
	init();
};
