
var mixAndApplyBugDemo = function(canvas, bgColor) {
    var assetManager;

    var DEMO_NAME = "Mix and Apply Bug Demo";

    function init () {
        assetManager = spineDemos.assetManager;
        assetManager.loadJson(DEMO_NAME, "MixAndApplyBug.json");
    }

    function loadingComplete () {
        startTest(loadSkeleton("Skeleton"), loadSkeleton('Skeleton'));
    }

    function startTest (skeletonObjects, other) {
        var skeleton = skeletonObjects.skeleton,
            otherSkeleton = other.skeleton,
            animationState = skeletonObjects.state,
            bone = skeleton.findBone('bone');

        animationState.setAnimation(0, 'translate_100_ms', false);
        animationState.addAnimation(0, 'scale_2_200_ms', false, 0);

        update(skeleton, animationState, 0.101); // Tick big enough to start the transition from one animation to the next.

        animationState.update(0.001); // For whatever reason the skeleton does not have the AnimationState applied in this update.

        update(skeleton, animationState, 0.2); // The previous animation (translate_100_ms) hangs and leaves its state

        console.log('The bone should have scale of 2 (', bone.scaleX === 2, ')(true) and translate of 0 (', bone.x === 0, ')(false)');
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
        var skeletonData = assetManager.get(DEMO_NAME, "MixAndApplyBug.json");
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

    mixAndApplyBugDemo.loadingComplete = loadingComplete;
    mixAndApplyBugDemo.render = render;
    mixAndApplyBugDemo.DEMO_NAME = DEMO_NAME;
    init();
};
